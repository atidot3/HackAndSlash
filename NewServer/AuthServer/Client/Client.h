#ifndef			__CLIENT__H_
#define			__CLIENT__H_

#include "Socket.h"

class Client
{
public:
	Client(SOCKET _connection, char* _ip);
	~Client();
	int		KeepAlive();
	SOCKET	getSocket();
	SOCKET	getUdp();
	void	AssignToken(char *_token);
	char	*ip;
	const char	*token;
private:
	Socket	*connection;
	Socket	*udp;
};

#endif			/*__CLIENT__H_*/