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
	WSAOVERLAPPED	*ovl;
	BOOL			result;
	DWORD			length = 0;
	CKey			*ck = new CKey;


	this->WSAinit();
	_isRunning = true;
	LOG("Server starting");
	if (!_accept.init())
		_isRunning = false;

	LOG("Server running");
	_accept.start();
	while (_isRunning)
	{
		LOG("RUNNING...");
		ovl = NULL;
		ck = NULL;
		result = GetQueuedCompletionStatus(_accept.getHandle(), &length, (PULONG_PTR)&ck, &ovl, INFINITE); // (controller, struct key, ???, ???, ???) bloquing funtion / gestion event
		switch (ck->op)
		{
			case Operation::ACCEPT:
			{
				_accept.accept(result, length, ck, ovl);
				break;
			}
			case Operation::READ:
			{
				std::cout << "ReadComplete" << std::endl;
				_accept.read_completed(result, length, ck, ovl);
				break;
			}
			case Operation::WRITE:
			{
				std::cout << "WriteComplete" << std::endl;
				break;
			}
			case Operation::UNKNOWN:
			{
				printf("* error, unknown operation!!!\n");
				break;
			}
			default:
				printf("* error, unknown operation!!!\n");
				break;
		}
	}

	delete ck;
	LOG("Server stopping");
	this->WSAClose();
	return;
	/*****************
	/////////\\\\\\\\\
	//!\\ IGNORE //!\\
	/////////\\\\\\\\\
	*****************/
	/*
	if (this->init() != 0)
	{
		std::cout << "Error while loading server" << std::endl;
		return;
	}
	unsigned int	port = m_config.wClientAcceptPort;
	Socket	cpy;

	_server.init(port);
	_server.Bind();
	_server.Listen();
	_select.setNdfs(_server);
//	_select.setTimeout(0, 50);
	std::cout << "Start Server on: " << m_config.ExternalIP << " " << m_config.wClientAcceptPort << std::endl;
	_isRunning = true;
	
//	std::thread		cio(&ServerApp::consoleIO, this);
//	std::thread		srv(&ServerApp::serverRun, this);

	while (_isRunning)
	{
#pragma region SELECT REGION
		if (_select.UpdateLoop(_server, cpy) < 0)
		{
			std::cerr << "Select Error: " << WSAGetLastError() << std::endl;
			_isRunning = false;
		}
		std::cout << sCMANAGER.getConnectedClient() << std::endl;
#pragma endregion
	}
//	cio.join();
//	srv.join();
	sCMANAGER.removeAllClient();
	std::cout << "Server Closed" << std::endl;
	_server.Close();
	this->WSAClose();
	*/
}