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
	IOMODE_UNKNOW,

	MAX_IOMODE
};

struct sIOCONTEXT : public OVERLAPPED
{
	WSABUF				wsabuf; // 
	eIOMODE				iomode;
	LPCVOID				param; // session ptr

	void Clear() { ZeroMemory(this, sizeof(sIOCONTEXT)); }
	void Reset() { ZeroMemory(this, sizeof(OVERLAPPED)); }
};

class Connection;

class Network
{
public:
	Network();
	~Network();

	int			Create();
	int			CreateListenSocket();
	int			Listen();
	int			CreateIOCP();
	int			CompleteIO(sIOCONTEXT * pIOContext, DWORD dwParam);
	HANDLE		getHandle(){ return m_hIOCP; }
	WSAOVERLAPPED	getOverlapped(){ return listener_ovl; }
	sIOCONTEXT	getSocketState(){ return listener_state; }



	int			PostAccept();
	void		CompleteAccept(DWORD dwTransferedBytes, Connection* pSession);
	int			PostRecv();
	int			CompleteRecv();
private:
	Socket		acceptSocket;
	Socket		listenSocket;
	SockAddr	addr;
	sIOCONTEXT  listener_state;
	WSAOVERLAPPED listener_ovl;
	HANDLE		m_hIOCP;
};

#endif /*NETWORK_H_*/