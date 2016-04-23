#ifndef		NETWORK_H_
# define	NETWORK_H_

#include		"Socket.hpp"
#include		<iostream>

# define	MAX_BUF  1024
# define	SERVER_ADDRESS  INADDR_LOOPBACK
# define	SERVICE_PORT  12345

enum eIOMODE
{
	IOMODE_ACCEPT = 1,
	IOMODE_CONNECT,
	IOMODE_RECV,
	IOMODE_SEND,

	MAX_IOMODE
};

typedef struct _SocketState // 
{
	eIOMODE operation;
	SOCKET socket;
	DWORD length;
	char buf[MAX_BUF];
} SocketState;


class Network
{
public:
	Network();
	~Network();

	int			Create();
	int			CreateListenSocket();
	int			Listen();
	int			CreateIOCP();
	int			PostAccept();
	int			CompleteIO(SocketState * pIOContext, DWORD dwParam);
	HANDLE		getHandle(){ return m_hIOCP; }
	WSAOVERLAPPED	getOverlapped(){ return listener_ovl; }
	SocketState	getSocketState(){ return listener_state; }
private:
	Socket		acceptSocket;
	Socket		listenSocket;
	SockAddr	addr;
	SocketState listener_state;
	WSAOVERLAPPED listener_ovl;
	HANDLE		m_hIOCP;
};

#endif /*NETWORK_H_*/