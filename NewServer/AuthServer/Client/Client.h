#ifndef			__CLIENT__H_
#define			__CLIENT__H_

#include "Socket.h"

class Packet;

class Client
{
public:
	Client(SOCKET _connection, char* _ip);
	~Client();
	int		KeepAlive();
	SOCKET	getSocket();
	Socket	*getSocketClass();
	Packet	*getSending();
	float	getLastKeepAlive(){return lastKeepAlive;}
	char	*ip;
private:
	Socket	*connection;
	float	lastKeepAlive;
};

#endif			/*__CLIENT__H_*/