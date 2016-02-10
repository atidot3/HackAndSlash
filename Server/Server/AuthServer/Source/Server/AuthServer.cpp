//-----------------------------------------------------------------------------------
//		Auth Server by Atidote @ Ragezone 
//-----------------------------------------------------------------------------------

#include "stdafx.h"
#include "AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

using namespace std;

//-----------------------------------------------------------------------------------
//		Load Realm database
//-----------------------------------------------------------------------------------
bool CAuthServer::LoadRealmlist(bool fromInit)
{
	m_authMutex.Lock();
	if (fromInit == true)
		NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Loading Realmlist...");

	db->prepare("SELECT * FROM realmd");
	db->execute();
	if ((db->rowsCount()) != 0)
	{
		int len = 0;
		while (db->fetch())
		{
			serverList[len].id = db->getInt("realmdID");
			serverList[len].port = db->getInt("port");
			memcpy(&serverList[len].ip, db->getString("ip").c_str(), 16);
			memcpy(&serverList[len].servername, db->getString("servername").c_str(), 16);
			if (db->getBoolean("online") == true)
				serverList[len].online = true;
			else
				serverList[len].online = false;
			serverList[len].len = len;
			std::string status = "";
			if (serverList[len].online == true && fromInit == true)
			{
				status = "online";
				NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Server: %d: %s / %s:%d, %s", serverList[len].id, serverList[len].servername, serverList[len].ip, serverList[len].port, status.c_str());
			}
			else if (serverList[len].online == false && fromInit == true)
			{
				status = "offline";
				NTL_PRINT(PRINT_APP, FOREGROUND_RED, "Server: %d: %s / %s:%d, %s", serverList[len].id, serverList[len].servername, serverList[len].ip, serverList[len].port, status.c_str());
			}
			
			len++;
		}
		serverNmb = len;
	}
	else
	{
		if (fromInit == true)
			NTL_PRINT(PRINT_APP, FOREGROUND_RED, "Error while loading Realmd, table empty.");
		m_authMutex.Unlock();
		db->closeStatm();
		return false;
	}
	db->closeStatm();
	m_authMutex.Unlock();
	return true;
}
//-----------------------------------------------------------------------------------
//		AuthServerMain
//-----------------------------------------------------------------------------------
int AuthServerMain(int argc, _TCHAR* argv[])
{
	NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Starting Auth-Server...");
	CAuthServer app;
	CNtlFileStream traceFileStream;

	// LOG FILE
	int rc = traceFileStream.Create("AuthLog");
	if (NTL_SUCCESS != rc)
	{
		printf("log file CreateFile error %d(%s)", rc, NtlGetErrorMessage(rc));
		return rc;
	}

	// CHECK INI FILE AND START PROGRAM
	NtlSetPrintStream(traceFileStream.GetFilePtr());
	NtlSetPrintFlag(PRINT_APP | PRINT_SYSTEM);

	rc = app.Create(argc, argv, ".\\Server.ini");
	if (NTL_SUCCESS != rc)
	{
		NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Server Application Create Fail %d(%s)", rc, NtlGetErrorMessage(rc));
		return rc;
	}

	// CONNECT TO MYSQL
	app.db = new MySQLConnWrapper;
	app.db->setConfig(app.GetConfigFileHost(), app.GetConfigFileUser(), app.GetConfigFilePassword(), app.GetConfigFileDatabase());
	try
	{
		app.db->connect();
		NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Connected to database server.");
	}
	catch (exception e)
	{
		NTL_PRINT(PRINT_APP, FOREGROUND_RED, "couldn't connect to database server ErrID:%s", e.what());
	}
	try
	{
		app.db->switchDb(app.GetConfigFileDatabase());
	}
	catch (exception e)
	{
		NTL_PRINT(PRINT_APP, FOREGROUND_RED, "Couldn't switch database to %s Error:%s", app.GetConfigFileDatabase(), e.what());
	}
	app.LoadRealmlist(true);
	app.Start();
	Sleep(500);
	NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Auth-Server Started.");
	app.WaitForTerminate();
	return 0;
}
