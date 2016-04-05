#include "Select.h"
#include "AuthServer.h"

Select::Select(Socket *sock, Socket *serverSock)
{
	storedSocket = sock;
	serverSocket = serverSock;
}
Select::~Select()
{

}
int			Select::waitFds(AuthServer* srv)
{
	int			ret;

	this->init(srv);
	ret = select(storedSocket->getSocket() + 1, &readfds, &writefds, NULL, NULL);
	return (ret);
}
bool		Select::isThereNewClient()
{
	if (FD_ISSET(serverSocket->getSocket(), &readfds))
	{
		return (true);
	}
	return (false);
}
void		Select::sendThings()
{

}
void		Select::recvThings(AuthServer *server)
{
	Client*	client;
	int		counter = 0;
	char	recvBuffer[1024];

	while ((client = server->getClient(counter)))
	{
		if (FD_ISSET(client->getSocket(), &readfds))
		{
			int readed = recv(server->getClient(counter)->getSocket(), recvBuffer, 1023, 0);
			if (readed <= 0)
			{
				closesocket(server->getClient(counter)->getSocket());
				server->removeClient(server->getClient(counter));
				--counter;
			}
			else if (readed > 0)
			{
				recvBuffer[readed] = '\0';
				send(server->getClient(counter)->getSocket(), recvBuffer, readed, 0);
			}
		}
		++counter;
	}
}
void		Select::init(AuthServer* srv)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(serverSocket->getSocket(), &readfds);
	Client*	client;
	int i = 0;

	while ((client = srv->getClient(i)))
	{
		if (srv->getClient(i)->getSocket() > storedSocket->getSocket())
			storedSocket = srv->getClient(i)->getSocketClass();
		FD_SET(srv->getClient(i)->getSocket(), &readfds);
		if (srv->getClient(i)->getSending() != NULL)
			FD_SET(srv->getClient(i)->getSocket(), &writefds);
		++i;
	}
}