#include "AuthServer.h"

using namespace std;

AuthServer::AuthServer()
{
	serverSocket = new Socket();
	udpReceiver = new Socket();
	running = false;
}
AuthServer::~AuthServer()
{
	delete serverSocket;
}
SOCKET		AuthServer::getSocket()
{
	return serverSocket->getSocket();
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
	udpReceiver->Create(true);
	udpReceiver->Bind();

	running = true;
	update_running = true;

	std::thread	serverThread(&AuthServer::Update, this);
	std::thread serverReceiverThread(&AuthServer::Receiver, this);

	
	while (serverSocket->waitFds(this) != -1)
	{
		if (serverSocket->isThereNewClient() == true)
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
	}
	running = false;
	update_running = false;
	serverThread.join();
	serverReceiverThread.join();
}
void		AuthServer::Receiver()
{
	while (update_running == true)
	{
		int SelectTiming = udpReceiver->recvfromTimeOutUDP(0, 0);
		switch (SelectTiming)
		{
		case 0:
			std::cout << "Timed out, do whatever you want to handle this situation" << std::endl;
			break;
		case -1:
			std::cout << "Error occurred, maybe we should display an error message?" << std::endl;
			break;
		default:
			// Ok the data is ready, call recvfrom() to get it then
			if (myClientList.size() > 0)
			{
				udpData *data = udpReceiver->recvThings(this);
				if (data != NULL)
				{
					// parse witch client send message
					serverMutex.lock();
					std::list<Client*>::iterator	it = myClientList.begin();
					while (it != myClientList.end())
					{
						if ((strcmp((*it)->ip, data->ip)) == 0)
						{
							std::cout << "client founded" << std::endl;
						}
						it++;
					}
					serverMutex.unlock();
				}
			}
			break;
		}
	}
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