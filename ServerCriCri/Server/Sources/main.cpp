/*
main.cpp for project Server_Test
Created on 24/1/2016
Update on 24/1/2016 8:33 PM

Copyright (c) 2016 Christian Chaumery
*/

#include	<Network/ServerApp.hpp>
#include	<list>
#include	<iostream>

class Server : public ServerApp
{
public:
	Server() {}
	~Server() {}

private:
	int	init()
	{
		//return OnConfiguration(".//Server.ini");
		return 0;
	}
	void	serverRun()
	{
		while (isRunning())
		{
			/*Sleep(20);
			_wqueue.push("Here is a new cmd");*/
		}
	}
};

int main()
{
	Server	serv;

	serv.run();
	/*
	IOCPServer server;

	server.Initialize();
	*/

	system("PAUSE");
	return 0;
}