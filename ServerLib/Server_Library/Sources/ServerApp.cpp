/*
	ServerApp.cpp for project Server_Library
	Created on 6/2/2016
	Update on 6/2/2016 3:50 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"ServerApp.hpp"
#include	<thread>

ServerApp::ServerApp()
{
	_isRunning = new std::atomic<bool>();
	*_isRunning = false;
	_list = new std::list<Socket>();
	_wqueue = new std::queue<std::string>();
}

ServerApp::~ServerApp()
{
	delete _list;
	delete _wqueue;
	*_isRunning = false;
	delete _isRunning;
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

	while (*_isRunning)
	{
		cmd = "";
		std::cin >> cmd;
		std::cout << "Command: " << cmd << std::endl;
		if (cmd == "stop")
			*_isRunning = false;
	}
}

void	ServerApp::run()
{
	this->WSAinit();

	unsigned int	port = 8888;
	Socket	cpy;
	int		ret = 0;
	std::string		cmd = "";

	this->init();

	_server.init(port);
	_server.Bind();
	_server.Listen();
	_select.setNdfs(_server);
	std::cout << "Start Server" << std::endl;
	*_isRunning = true;

	std::thread		cio(&ServerApp::consoleIO, this);
	std::thread		srv(&ServerApp::serverRun, this);

	while (*_isRunning)
	{
		_select.zero();
		_select.set(_server, Select::READ);
		for (iterator it = _list->begin(); it != _list->end(); ++it)
		{
			_select.set((*it), Select::READ);
			_select.set((*it), Select::WRITE);
		}
		if ((ret = _select.start()) < 0)
		{
			std::cerr << "Select Error: " << WSAGetLastError() << std::endl;
			*_isRunning = false;
		}
		else if (_select.isset(_server, Select::READ))
		{
			cpy = _server.Accept();
			if (cpy.getState() != Socket::INACTIVE)
			{
				_list->push_back(cpy);
				std::cout << "A client is connected" << std::endl;
				_server.Send(cpy, std::string("Hello World !"));
				_select.setNdfs(cpy);
			}
		}
		else
		{
			cmd = "";
			for (iterator it = _list->begin(); it != _list->end(); ++it)
				if (_select.isset(*it, Select::READ))
					if (_server.Recv(*it, cmd) <= 0)
					{
						std::cout << "A client has quitted" << std::endl;
						it->Close();
						it = _list->erase(it);
					}
			if (_wqueue->size() > 0 && _list->size() > 0)
			{
				cmd = _wqueue->front();
				_wqueue->pop();
				for (iterator it = _list->begin(); it != _list->end(); ++it)
					if (_select.isset(*it, Select::WRITE))
						if ((_server.Send(*it, cmd)) <= 0)
							std::cerr << "Error while writing to client: " << WSAGetLastError() << std::endl;
			}
		}
	}
	cio.join();
	srv.join();
	for (iterator it = _list->begin(); it != _list->end(); ++it)
		it->Close();

	std::cout << "Server Closed" << std::endl;
	_server.Close();
	this->WSAClose();
}