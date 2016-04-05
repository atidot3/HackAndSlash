#include "Client.h"

Client::Client(SOCKET _connection, char* _ip)
{
	connection = new Socket(_connection);
	ip = _ip;
	lastKeepAlive = 0;
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
	if (connection == NULL)
		return NULL;
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