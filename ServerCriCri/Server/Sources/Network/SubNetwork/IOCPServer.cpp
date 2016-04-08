#include "IOCPServer.h"

IOCPServer::IOCPServer()
{
	g_ServerSocket = INVALID_SOCKET;
	g_hIOCP = INVALID_HANDLE_VALUE;
}


IOCPServer::~IOCPServer()
{
	closesocket(g_ServerSocket);
	WSACleanup();
}
DWORD WINAPI IOCPServer::WorkerThread(LPVOID WorkThreadContext)
{
	return 0;
}
void IOCPServer::Initialize()
{
	ZeroMemory(&wsaData, sizeof(WSADATA));
	int retVal = -1;
	if ((retVal = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		std::cout << "failed to initialize WSA" << std::endl;
	}
	{	// create socket
		g_ServerSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (g_ServerSocket == INVALID_SOCKET) 
		{
			std::cout << "Server Socket Creation Failed::Reason Code::" << WSAGetLastError() << std::endl;
			return;
		}
	}
	{   //bind  
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = htonl(INADDR_ANY);
		service.sin_port = htons(12345);
		int retVal = bind(g_ServerSocket, (SOCKADDR *)&service, sizeof(service));
		if (retVal == SOCKET_ERROR) 
		{
			std::cout << "Server Soket Bind Failed::Reason Code::" << WSAGetLastError() << std::endl;
			return;
		}
	}
	{   //listen  
		int retVal = listen(g_ServerSocket, 8);
		if (retVal == SOCKET_ERROR)
		{
			std::cout << "Server Socket Listen Failed::Reason Code::" << WSAGetLastError() << std::endl;
			return;
		}
	}
	{   // Create IOCP  
		SYSTEM_INFO sysInfo;
		ZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
		GetSystemInfo(&sysInfo);
		g_ThreadCount = sysInfo.dwNumberOfProcessors * 1;
		g_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, g_ThreadCount);
		if (g_hIOCP == NULL) 
		{
			std::cout << "CreateIoCompletionPort() Failed::Reason::" << GetLastError() << std::endl;
			return;
		}
		if (CreateIoCompletionPort((HANDLE)g_ServerSocket, g_hIOCP, 0, 0) == NULL)
		{
			std::cout << "Binding Server Socket to IO Completion Port Failed::Reason Code::" << GetLastError() << std::endl;
			return;
		}
	}
	{  //Create worker threads  
		for (DWORD dwThread = 0; dwThread < g_ThreadCount; dwThread++)
		{
			HANDLE  hThread;
			DWORD   dwThreadId;
			hThread = CreateThread(NULL, 0, &IOCPServer::WorkerThread, 0, 0, &dwThreadId);
			CloseHandle(hThread);
		}
	}
	std::cout << "Server initialized, IOCP started." << std::endl;
	{ //accept new connection  
		while (1)
		{
			std::cout << "Waiting for new connection." << std::endl;
			SOCKET ls = accept(g_ServerSocket, NULL, NULL);
			if (ls == SOCKET_ERROR)
				break;
			std::cout << "Client connected." << std::endl;
			{ //diable buffer to improve performance  
				int nZero = 0;
				setsockopt(ls, SOL_SOCKET, SO_SNDBUF, (char *)&nZero, sizeof(nZero));
			}
			if (CreateIoCompletionPort((HANDLE)ls, g_hIOCP, 0, 0) == NULL)
			{
				std::cout << "Binding Client Socket to IO Completion Port Failed::Reason Code::" << GetLastError() << std::endl;
				closesocket(ls);
			}
			else
			{ 
				IO_DATA * data = new IO_DATA;
				ZeroMemory(&data->Overlapped, sizeof(data->Overlapped));
				ZeroMemory(data->Buffer, sizeof(data->Buffer));
				data->opCode = IO_READ;
				data->nTotalBytes = 0;
				data->nSentBytes = 0;
				data->wsabuf.buf = data->Buffer;
				data->wsabuf.len = sizeof(data->Buffer);
				data->activeSocket = ls;
				DWORD dwRecvNumBytes = 0, dwFlags = 0;
				int nRet = WSARecv(ls, &data->wsabuf, 1, &dwRecvNumBytes,
					&dwFlags,
					&data->Overlapped, NULL);
				if (nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()))
				{
					std::cout << "WASRecv Failed::Reason Code::" << WSAGetLastError() << std::endl;
					closesocket(ls);
					delete data;
				}
			}
		}
	}
}
