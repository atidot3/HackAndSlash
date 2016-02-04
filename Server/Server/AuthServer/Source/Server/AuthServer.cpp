//-----------------------------------------------------------------------------------
//		Auth Server by Daneos @ Ragezone 
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

/*void CAuthServer::Update(DWORD diff)
{
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		it->second->Update(diff);
	}
}*/
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//		AuthServerMain
//-----------------------------------------------------------------------------------
int AuthServerMain(int argc, _TCHAR* argv[])
{
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
	app.Start();
	Sleep(500);
	std::cout << "\t______           AKCore :O 2015					______\n\n" << std::endl;
	std::string sCommand = "";
	while (true)
	{
		cout << "Server> ";
		getline(cin, sCommand);
		if (!sCommand.empty())
		{
			cout << "Server> " << sCommand.c_str() << std::endl;
		}
	}
	app.WaitForTerminate();
	return 0;
}
