/*
ClientManager.h for project Server_Library
Created on 06/04/2016
Update on 06/04/2016

Copyright (c) 2016 Entringer Antony
*/

#ifndef		CLIENTMANAGER_H_
# define	CLIENTMANAGER_H_

#include <list>
#include <iostream>
#include <mutex>

#include "Client.h"

class ClientManager
{
public:
	static ClientManager& Instance();
	ClientManager();
	~ClientManager();
	void				AddClient(Client*);
	Client*				getClient(int); // loop client until null
	void				removeClient(Client*);
	void				removeAllClient();
	int					getConnectedClient();
private:
	std::list<Client*>	clientList;
	std::mutex			mutex;
	static ClientManager m_instance;
};

#define sCMANAGER ClientManager::Instance()

#endif		/*CLIENTMANAGER_H_*/