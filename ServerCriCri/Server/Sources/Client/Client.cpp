/*
ClientManager.h for project Server_Library
Created on 06/04/2016
Update on 06/04/2016

Copyright (c) 2016 Entringer Antony
*/
#include "Client.h"

Client::Client()
{
}
Client::Client(Socket *_socket, std::string _token)
{
	socket = _socket;
	token = _token;
}
Client::~Client()
{
}
SOCKET		Client::getSOCKET()
{
	return socket->getRawSocket();
}
Socket		*Client::getSocket()
{
	return socket;
}