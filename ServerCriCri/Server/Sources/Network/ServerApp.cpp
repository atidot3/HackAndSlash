/*
	ServerApp.cpp for project Server_Library
	Created on 6/2/2016
	Update on 6/2/2016 3:50 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/ServerApp.hpp"
#include	"IniReader.h"
#include	<thread>

#define		SERVER_LOG_FILE		"./Server.log"

ServerApp::ServerApp()
{
	_isRunning = false;
	Logger::getInstance().registerFile("./Server.log");
	LOGFILE(SERVER_LOG_FILE, "Server Started");
}

ServerApp::~ServerApp()
{
	LOGFILE(SERVER_LOG_FILE, "Server Stopped");
	_isRunning = false;
}

void	ServerApp::WSAinit()
{
#ifdef WIN32
	WSADATA		_WSAData;
	WSAStartup(MAKEWORD(2, 0), &_WSAData);
#endif
}

void	ServerApp::WSAClose()
{
#ifdef WIN32
	WSACleanup();
#endif
}

void	ServerApp::consoleIO()
{
	std::string	cmd;

	Logger::getInstance();
	while (_isRunning)
	{
		cmd = "";
		std::cin >> cmd;
		std::cout << "Command: " << cmd << std::endl;
		if (cmd == "stop")
			_isRunning = false;
	}
}
int		ServerApp::OnConfiguration(const char * lpszConfigFile)
{
	IniFile file;

	int rc = file.Create(lpszConfigFile);
	if (0 != rc)
	{
		std::cout << "No such file "<< lpszConfigFile << std::endl;
		return rc;
	}
	if (!file.Read("IPAddress", "Address", m_config.ExternalIP))
	{
		std::cout << "loading " << "Address" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("Auth Server", "Address", m_config.strClientAcceptAddr))
	{
		std::cout << "loading " << "Game Server Address" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("Auth Server", "Port", m_config.wClientAcceptPort))
	{
		std::cout << "loading " << "Port" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("DATABASE", "Host", m_config.Host))
	{
		std::cout << "loading " << "Host" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("DATABASE", "User", m_config.User))
	{
		std::cout << "loading " << "User" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("DATABASE", "Password", m_config.Password))
	{
		std::cout << "loading " << "Password" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("DATABASE", "Db", m_config.Database))
	{
		std::cout << "loading " << "Db" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("PERFORMANCE", "PlayerLimit", m_config.PlayerLimits))
	{
		std::cout << "loading " << "PlayerLimit" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("PERFORMANCE", "PlayerSaveInterval", m_config.saveInterval))
	{
		std::cout << "loading " << "PlayerSaveInterval" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("PERFORMANCE", "PlayerSaveStatsSaveOnlyOnLogout", m_config.SaveOnLogout))
	{
		std::cout << "loading " << "PlayerSaveStatsSaveOnlyOnLogout" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("REALMD", "realmid", m_config.realmid))
	{
		std::cout << "loading " << "realmid" << " failed" << std::endl;
		return -1;
	}
	return 0;
}
void	ServerApp::run()
{
	int rc = 0;
	_isRunning = true;
	BOOL bResult = FALSE;
	DWORD dwBytesTransferred = 0;

	if (network.Create() != 0)
		return;
	if (network.CreateIOCP() != 0)
		return;
	if (network.CreateListenSocket() != 0)
		return;
	if (network.Listen() != 0)
		return;
	if (network.PostAccept() != 0)
		return;
	while (isRunning())
	{
		sIOCONTEXT* state = NULL;
		Connection * pSession = NULL;

		bResult = GetQueuedCompletionStatus(network.getHandle(), &dwBytesTransferred, (ULONG_PTR*)&pSession, (LPOVERLAPPED*)&state, INFINITE);
		if (!bResult)
		{
			DWORD err = GetLastError();
			printf("* error %d getting completion port status!!!\n", err);
			return;
		}
		if (NULL == state)
		{
			printf("NULL == network.getOverlapped()");
			continue;
		}
		else
		{
			std::cout << state->iomode << std::endl;
			switch (state->iomode)
			{
				case IOMODE_ACCEPT:
				{
					std::cout << "ACCEPT PENDING" << std::endl;
					network.CompleteAccept(dwBytesTransferred, pSession);
					//delete newConnection; // CRASH WHY
					if (pSession != NULL)
					{
						// store it ?
						//pSession->OnAccept();
						//sCMANAGER.AddClient(pSession);
						//send(pSession->clientSock->GetRawSocket(), "Salut", 5, 0);
					}
					break;
				}
				case IOMODE_CONNECT:
				{
					std::cout << "CONNECT PENDING" << std::endl;
					//return CompleteConnect(dwParam);
					break;
				}
				case IOMODE_RECV:
				{
					std::cout << "RECV PENDING" << std::endl;
					//return CompleteRecv(dwParam);
					break;
				}
				case IOMODE_SEND:
				{
					std::cout << "SEND PENDING" << std::endl;
					//return CompleteSend(dwParam);
					break;
				}
				case IOMODE_UNKNOW:
				{
					std::cout << "* error, IOMODE_UNKNOW unknown operation!!!\n" << std::endl;
					break;
				}
				default:
					std::cout << "* error, unknown operation!!!\n" << std::endl;
					break;
			}
			network.PostAccept();
		}
	}
}