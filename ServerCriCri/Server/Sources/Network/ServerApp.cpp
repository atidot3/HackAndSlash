/*
	ServerApp.cpp for project Server_Library
	Created on 6/2/2016
	Update on 6/2/2016 3:50 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/ServerApp.hpp"
#include	"IniReader.h"
#include	<thread>

ServerApp::ServerApp()
{
	_isRunning = false;
}

ServerApp::~ServerApp()
{
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
	if (!file.Read("Game Server", "Address", m_config.strClientAcceptAddr))
	{
		std::cout << "loading " << "Game Server Address" << " failed" << std::endl;
		return -1;
	}
	if (!file.Read("Game Server", "Port", m_config.wClientAcceptPort))
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
	this->WSAinit();

	unsigned int	port = 12345;
	Socket	cpy;
	int		ret = 0;
	std::string		cmd = "";

	if (this->init() != 0)
	{
		std::cout << "Error while loading server" << std::endl;
		return;
	}

	_server.init(port);
	_server.Bind();
	_server.Listen();
	_select.setNdfs(_server);
//	_select.setTimeout(0, 50);
	std::cout << "Start Server" << std::endl;
	_isRunning = true;

	std::thread		cio(&ServerApp::consoleIO, this);
//	std::thread		srv(&ServerApp::serverRun, this);

	while (_isRunning)
	{
		_select.zero();
		_select.set(_server, Select::READ);
		for (iterator it = _list.begin(); it != _list.end(); ++it)
		{
			_select.set((*it), Select::READ);
//			_select.set((*it), Select::WRITE);
		}
		if ((ret = _select.start()) < 0)
		{
			std::cerr << "Select Error: " << WSAGetLastError() << std::endl;
			_isRunning = false;
		}
		else if (_select.isset(_server, Select::READ))
		{
			cpy = _server.Accept();
			if (cpy.getState() != Socket::INACTIVE)
			{
				_list.push_back(cpy);
				std::cout << "A client is connected" << std::endl;
				std::cout << "There is " << _list.size() << " Clients connected." << std::endl;
				_server.Send(cpy, std::string("Hello World !"));
				_select.setNdfs(cpy);
			}
		}
		else
		{
			cmd = "";
			for (iterator it = _list.begin(); it != _list.end(); ++it)
				if (_select.isset(*it, Select::READ))
					if (_server.Recv(*it, cmd) <= 0)
					{
						std::cout << "A client has quitted" << std::endl;
						it->Close();
						it = _list.erase(it);
					}
					//else
						// std::cout << "Message from " << it->getAddr() << ": " << cmd << std::endl;
			/*
			if (_wqueue->size() > 0 && _list->size() > 0)
			{
				cmd = _wqueue->front();
				_wqueue->pop();
				for (iterator it = _list->begin(); it != _list->end(); ++it)
					if (_select.isset(*it, Select::WRITE))
						if ((_server.Send(*it, cmd)) <= 0)
							std::cerr << "Error while writing to client: " << WSAGetLastError() << std::endl;
			}
			*/
		}
	}
	cio.join();
//	srv.join();
	for (iterator it = _list.begin(); it != _list.end(); ++it)
		it->Close();

	std::cout << "Server Closed" << std::endl;
	_server.Close();
	this->WSAClose();
}