//-----------------------------------------------------------------------------------
//		Auth Server by Atidote @ Ragezone 
//-----------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>
#include <csignal>

using namespace std;

void CAuthServer::Update()
{
	//Charmanager->Run();
}
//-----------------------------------------------------------------------------------

void CAuthServer::PrepareServer(bool online)
{
	db->prepare("UPDATE realmd SET online=? WHERE realmdID=?");
	if (online == false)
		db->setInt(1, 0);
	else
		db->setInt(1, 1);
	db->setInt(2, m_config.realmid);
	db->execute();
	db->closeStatm();
}

void signalHandler(int signum)
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	app->PrepareServer(false);
}

//-----------------------------------------------------------------------------------
//		AuthServerMain
//-----------------------------------------------------------------------------------
int AuthServerMain(int argc, _TCHAR* argv[])
{
	signal(SIGINT, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGSEGV, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGBREAK, signalHandler);

	NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Starting Game-Server...");
	CAuthServer app;
	CNtlFileStream traceFileStream;

	// LOG FILE
	int rc = traceFileStream.Create("GameLog");
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
	app.Charmanager = new CharacterManager();
	app.PrepareServer(true);
	app.Start();
	Sleep(500);
	NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "Game-Server Started.");
	std::string sCommand = "";
	/*while (app.IsRunnable())
	{
		cout << "Server> ";
		getline(cin, sCommand);
		if (!sCommand.empty())
		{
			cout << "Server> " << sCommand.c_str() << std::endl;
		}
	}*/
	// register signal SIGINT and signal handler
	app.WaitForTerminate();
	return 0;
}
