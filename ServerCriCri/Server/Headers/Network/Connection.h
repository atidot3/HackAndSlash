#ifndef		CONNECTION_H_
# define	CONNECTION_H_

#include	"Network.h"

const DWORD CONNECTION_KEEP_ALIVE_CHECK_TIME = 15 * 1000;

class Connection
{
public:
	Connection();
	Connection(Socket *);
	~Connection();

	int								OnConnect() { return 0; }
	int								OnAccept() { return 0; }

	int								getSOCKET(){ return 0; }
	int PostRecv();
	Socket *clientSock;
};

#endif /*CONNECTION_H_*/