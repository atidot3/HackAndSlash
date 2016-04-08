#ifndef IOCPSERVER_H
#define IOCPSERVER_H

#include <winsock2.h>  
#include <mswsock.h>  
#include <windows.h>  
#include <iostream>
#include <cstdlib>

#pragma comment(lib,"ws2_32.lib") 

#define MAX_BUFF_SIZE                8192  

class IOCPHandler;

enum							IO_OPERATION{ IO_READ, IO_WRITE };
struct							IO_DATA
{
	WSAOVERLAPPED               Overlapped;
	char                        Buffer[MAX_BUFF_SIZE];
	WSABUF                      wsabuf;
	int                         nTotalBytes;
	int                         nSentBytes;
	IO_OPERATION                opCode;
	SOCKET                      activeSocket;
};

class IOCPServer
{
public:
	IOCPServer();
	~IOCPServer();
	void						Initialize();
	static DWORD WINAPI			WorkerThread(LPVOID WorkThreadContext);
private:
	WSADATA						wsaData;
	SOCKET						g_ServerSocket;
	sockaddr_in					service;
	int							g_ThreadCount;
	HANDLE						g_hIOCP;
};

#endif