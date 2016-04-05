#include "AuthServer.h"

using namespace std;

AuthServer::AuthServer()
{
	serverSocket = new Socket();
	select = new Select(serverSocket);
	running = false;
	std::cout << sAuth << " " << this << std::endl;
}
AuthServer::~AuthServer()
{
	delete serverSocket;
}
SOCKET		AuthServer::getSocket()
{
	return serverSocket->getSocket();
}
AuthServer*	AuthServer::instance()
{
	static AuthServer instance;
	return &instance;
}
Client*		AuthServer::getClient(int position)
{
	serverMutex.lock();
	std::list<Client*>::iterator	it;
	int i;

	for (i = 0, it = myClientList.begin(); i < position && it != myClientList.end(); i++, it++);
	if (it == myClientList.end())
	{
		serverMutex.unlock();
		return NULL;
	}
	else 
	{
		serverMutex.unlock();
		return (*it);
	}
}
bool		AuthServer::isClientIpExist(char *ip)
{
	serverMutex.lock();
	std::list<Client*>::iterator	it = myClientList.begin();
	while (it != myClientList.end())
	{
		if (strcmp((*it)->ip, ip) == 0)
		{
			serverMutex.unlock();
			return true;
		}
		it++;
	}
	serverMutex.unlock();
	return false;
}
void		AuthServer::Start()
{
	serverSocket->Create(false);
	serverSocket->Bind();
	serverSocket->Listen();

	running = true;
	update_running = true;

	std::thread	serverThread(&AuthServer::Update, this);
	
	while (select->waitFds() != -1)
	{
		if (select->isThereNewClient() == true)
		{
			Client* newClient = serverSocket->Accept();
			//if (isClientIpExist(newClient->ip) == false)
			//{
				serverMutex.lock();
				if (newClient != NULL)
				{
					myClientList.push_back(newClient);
					printf("Client from %s created\n", newClient->ip);
				}
				serverMutex.unlock();
			//}
			//else
			//{
				// send error
			//}
		}		
		select->recvThings(this);
	}
	running = false;
	update_running = false;
	serverThread.join();
}
void		AuthServer::Update()
{
	std::list<Client*>::iterator	it;

	while (update_running == true)
	{
		serverMutex.lock();
		it = myClientList.begin();
		while (it != this->myClientList.end())
		{
			if (((*it)->KeepAlive()) == SOCKET_ERROR)
			{
				closesocket((*it)->getSocket());
				delete (*it);
				it = myClientList.erase(it);
			}
			else
				it++;
		}
		serverMutex.unlock();
		std::cout << "Current connected players: " << myClientList.size() << std::endl;
		Sleep(1000);
	}
}