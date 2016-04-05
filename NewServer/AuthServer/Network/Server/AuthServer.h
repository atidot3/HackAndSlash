#ifndef		 __AUTHSERVER__H_
#define		 __AUTHSERVER__H_

#include "Socket.h"
#include "Select.h"
#include "Client.h"
#include <thread>
#include <iostream>
#include <map>
#include <mutex>

// 2000 player / 5 thread = 400 player per thread

class AuthServer
{
public:
	static				AuthServer* instance();
	AuthServer();
	~AuthServer();
	void				Start();
	void				Update();
	SOCKET				getSocket();
	Client				*getClient(int position);
	bool				isClientIpExist(char *ip);
private:
	bool				running;
	bool				update_running;
	Socket				*serverSocket;
	Select				*select;
	std::list<Client*>	myClientList;
	std::mutex			serverMutex;
};

#define sAuth AuthServer::instance()

#endif /*__AUTHSERVER__H_*/