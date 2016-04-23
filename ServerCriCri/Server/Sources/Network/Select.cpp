/*
	Select.cpp for project Server_Library
	Created on 8/2/2016
	Update on 8/2/2016 11:12 AM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/Select.hpp"
#include	"Client.h"
#include	"ClientManager.h"

Select::Select()
{
	_nfds = 0;
	_timeout.tv_sec = 0;
	_timeout.tv_usec = 10000;
}

Select::~Select()
{
}
int	Select::UpdateLoop(Socket &server, Socket& cpy)
{
	/*int	counter = 0;
	Client*	client;
	std::string		cmd = "";

	zero();
	set(server, Select::READ);
	counter = 0;
	while ((client = sCMANAGER.getClient(counter)))
	{
		set(client->getSocket(), Select::READ);
		++counter;
	}
	if (start() < 0)
		return -1;
	else if (isset(server, Select::READ))
	{
		server.Accept(cpy);
		if (cpy.getState() != Socket::INACTIVE)
		{
			server.Send(cpy, std::string("Hello World !"));
			setNdfs(cpy);
			sCMANAGER.AddClient(new Client(cpy, "H3ll0 w0rld")); // NEED GENERATE TOKEN
			//LOG("A client from " + cpy.getAddr() + " is connected!");
			//LOGFILE(SERVER_LOG_FILE, "A client from " + cpy.getAddr() + " is connected!");
			//std::cout << "Connected client: " << sCMANAGER.getConnectedClient() << std::endl;
		}
	}
	else
	{
		cmd = "";
		counter = 0;
		while ((client = sCMANAGER.getClient(counter)))
		{
			if (isset(client->getSocket(), Select::READ))
			{
				if (server.Recv(client->getSocket(), cmd) <= 0)
				{
					//LOG("A client from " + cpy.getAddr() + " is disconnected!");
					//LOGFILE(SERVER_LOG_FILE, "A client from " + cpy.getAddr() + " is disconnected!");
					sCMANAGER.removeClient(client);
					//std::cout << "Connected client: " << sCMANAGER.getConnectedClient() << std::endl;
					--counter;
				}
				else
				{
					//std::cout << "Receiving " << cmd << std::endl;
					server.Send(client->getSocket(), std::string("Hello World !"));
				}
			}
			++counter;
		}
	}*/
	return 0;
}
void Select::zero()
{
	FD_ZERO(&_rdfs);
	FD_ZERO(&_wrfs);
	FD_ZERO(&_exfs);
}

void Select::set(Socket &sock, Type type)
{
	/*if (type == READ)
		FD_SET(sock.getRawSocket(), &_rdfs);
	else if (type == WRITE)
		FD_SET(sock.getRawSocket(), &_wrfs);
	else if (type == EXCEPT)
		FD_SET(sock.getRawSocket(), &_exfs);*/
}

int Select::isset(Socket &sock, Type type)
{
	/*if (type == READ)
		return FD_ISSET(sock.getRawSocket(), &_rdfs);
	else if (type == WRITE)
		return FD_ISSET(sock.getRawSocket(), &_wrfs);
	else if (type == EXCEPT)
		return FD_ISSET(sock.getRawSocket(), &_exfs);*/
	return false;
}

int Select::start()
{
	return select((int)_nfds + 1, &_rdfs, &_wrfs, &_exfs, &_timeout);
}

void Select::setNdfs(Socket &sock)
{
	//_nfds = sock.getRawSocket() > _nfds ? sock.getRawSocket() : _nfds;
}

void Select::setTimeout(long tv_sec, long tv_usec)
{
	_timeout.tv_sec = tv_sec;
	_timeout.tv_usec = tv_usec;
}
