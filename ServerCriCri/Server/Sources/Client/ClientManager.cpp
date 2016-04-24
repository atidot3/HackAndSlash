/*
ClientManager.h for project Server_Library
Created on 06/04/2016
Update on 06/04/2016

Copyright (c) 2016 Entringer Antony
*/
#include "ClientManager.h"

ClientManager ClientManager::m_instance = ClientManager();

ClientManager::ClientManager()
{

}
ClientManager::~ClientManager()
{

}
ClientManager& ClientManager::Instance()
{
	return m_instance;
}
void		ClientManager::AddClient(Connection* _client)
{
	mutex.lock();
	clientList.push_back(_client);
	mutex.unlock();
}
Connection*		ClientManager::getClient(int index)
{
	mutex.lock();
	std::list<Connection*>::iterator	it;
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
void		ClientManager::removeClient(Connection* client)
{
	mutex.lock();
	std::list<Connection*>::iterator	it = clientList.begin();
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
	std::list<Connection*>::iterator	it = clientList.begin();
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