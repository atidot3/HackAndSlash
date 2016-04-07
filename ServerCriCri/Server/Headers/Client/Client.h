/*
ClientManager.h for project Server_Library
Created on 06/04/2016
Update on 06/04/2016

Copyright (c) 2016 Entringer Antony
*/
#ifndef		CLIENT_H_
# define	CLIENT_H_

#include "Socket.hpp"

class Client
{
public:
	Client();
	~Client();
	Client(Socket &, std::string);
	SOCKET			getSOCKET();
	Socket			&getSocket();

	bool	operator==(Client &client) { return this->getSOCKET() == client.getSOCKET(); }
private:
	Socket			socket;
	std::string		token;

private: // GAME VARIABLE
	int		AccountID;
};

#endif		/*CLIENT_H_*/