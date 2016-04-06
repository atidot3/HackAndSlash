/*
ClientManager.h for project Server_Library
Created on 06/04/2016
Update on 06/04/2016

Copyright (c) 2016 Entringer Antony
*/
#include "ClientManager.h"

ClientManager::ClientManager()
{

}
ClientManager::~ClientManager()
{

}
void		ClientManager::AddClient(Client* _client)
{
	mutex.lock();
	clientList.push_back(_client);
	mutex.unlock();
}
Client*		ClientManager::getClient(int index)
{
	mutex.lock();
	std::list<Client*>::iterator	it;
	int i;

	for (i = 0, it = clientList.begin(); i < index && it != clientList.end(); i++, it++);
	if (it == clientList.end())
	{
		mutex.unlock();
		return NULL;
	}
	else
	{
		mutex.unlock();
		return (*it);
	}
	mutex.unlock();
	return NULL;
}
void		ClientManager::removeClient(Client* client)
{
	mutex.lock();
	std::list<Client*>::iterator	it = clientList.begin();
	while (it != clientList.end())
	{
		if ((*it) == client)
		{
			std::cout << "Client nb " << (*it)->getSOCKET() << " deleted!" << std::endl;
			delete (*it);
			it = clientList.erase(it);
			break;
		}
		it++;
	}
	mutex.unlock();
}
void		ClientManager::removeAllClient()
{
	mutex.lock();
	std::list<Client*>::iterator	it = clientList.begin();
	while (it != clientList.end())
	{
		delete (*it);
		it = clientList.erase(it);
		it++;
	}
	mutex.unlock();
}
int			ClientManager::getConnectedClient()
{
	return (int)clientList.size();
}