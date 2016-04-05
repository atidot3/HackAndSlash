#ifndef			__SOCKET__H_
#define			__SOCKET__H_

#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <list>
#include <string>

#define DEFAULT_PORT	"12345"
#define RECV_PORT		"12346"

class AuthServer;
class Client;

struct udpData
{
	char *ip;
	char *message;
};

class Socket
{
public:
	Socket(int port = 0);
	Socket(SOCKET s);
	~Socket();
	int							Create(bool isUdp = false);
	int							Bind();
	int							Listen();
	Client*						Accept();
	SOCKET						getSocket();
	int							waitFds(AuthServer *server);
	void						init(AuthServer *server);
	bool						isThereNewClient();
	udpData						*recvThings(AuthServer *server);
	int							recvfromTimeOutUDP(long sec, long usec);
private:
	WSADATA						wsaData;
	struct addrinfo				*result = NULL;
	struct addrinfo				hints;
	int							iResult;
	int							iSendResult;
	int							init();
	int							start();
	SOCKET						sock;
	fd_set						readfds;
	fd_set						writefds;
	SOCKADDR_IN                 ClientAddr;
	int                         ClientAddrLen;
	bool						udp;
};

#endif // !__SOCKET__H_
