#include "Client.h"

Client::Client(SOCKET _connection, char* _ip)
{
	connection = new Socket(_connection);
	ip = _ip;
	//	printf("Client from %s created\n", ip);
}
Client::~Client()
{
	delete connection;
}
int		Client::KeepAlive()
{
	return send(getSocket(), "0", sizeof("0"), 0);
}
SOCKET	Client::getSocket()
{
	return connection->getSocket();
}
Socket	*Client::getSocketClass()
{
	return connection;
}
Packet*	Client::getSending()
{
	return NULL;
}