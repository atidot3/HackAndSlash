#include "Select.h"
#include "AuthServer.h"

Select::Select(Socket *sock)
{
	storedSocket = sock;
}
Select::~Select()
{

}
int			Select::waitFds()
{
	int			ret;

	this->init();
	ret = select(storedSocket->getSocket() + 1, &readfds, &writefds, NULL, NULL);
	return (ret);
}
bool		Select::isThereNewClient()
{
	if (FD_ISSET(storedSocket->getSocket(), &readfds))
		return (true);
	return (false);
}
void		Select::sendThings()
{

}
void		Select::recvThings(AuthServer *server)
{
	std::cout << "recvThings" << std::endl;
	Client*	client;
	int		counter = 0;
	char	recvBuffer[1024];

	while ((client = sAuth->getClient(counter)))
	{
		std::cout << "WHILE" << std::endl;
		if (FD_ISSET(client->getSocket(), &readfds))
		{
			std::cout << "Something is in the socket !" << std::endl;
			int readed = recv(client->getSocket(), recvBuffer, 1023, 0);
			if (readed > 0)
			{
				recvBuffer[readed] = '\0';
				printf("%s\n", recvBuffer);
			}
			else
			{
				printf("%s\n", "DAFUK");
			}
		}
		else
		{
			std::cout << "???" << std::endl;
		}
		counter++;
	}
	std::cout << "recvThings end" << std::endl;
}
void		Select::init()
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_SET(storedSocket->getSocket(), &readfds);
	Client*	client;
	int i = 0;

	while ((client = sAuth->getClient(i)))
	{
		if (sAuth->getClient(i)->getSocket() > storedSocket->getSocket())
			storedSocket = sAuth->getClient(i)->getSocketClass();
		FD_SET(sAuth->getClient(i)->getSocket(), &readfds);
		if (sAuth->getClient(i)->getSending() != NULL)
			FD_SET(sAuth->getClient(i)->getSocket(), &writefds);
		++i;
	}
}