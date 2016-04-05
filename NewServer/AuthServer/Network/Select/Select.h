#ifndef			__SELECT__H_
#define			__SELECT__H_

#include "Socket.h"

class AuthServer;

class Select
{
public:
	Select(Socket*, Socket*);
	~Select();
	int			waitFds(AuthServer*);
	fd_set		getReadFds();
	fd_set		getWriteFds();
	bool		isThereNewClient();
	void		sendThings();
	void		recvThings(AuthServer*);
private:
	Socket		*storedSocket;
	Socket		*serverSocket;
	fd_set		readfds;
	fd_set		writefds;
private:
	void		init(AuthServer*);
};

#endif			/*__SELECT__H_*/