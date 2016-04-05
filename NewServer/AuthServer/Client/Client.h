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
	char	*ip;
private:
	Socket	*connection;
};

#endif			/*__CLIENT__H_*/