#include "Client.h"

Client::Client(SOCKET _connection, char* _ip)
{
	connection = new Socket(_connection);
	udp = new Socket();
	udp->Create(true);
	ip = _ip;
	//	printf("Client from %s created\n", ip);
}
void	Client::AssignToken(char *_token)
{
	token = _token;
	std::cout << "token: " << token << std::endl;
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