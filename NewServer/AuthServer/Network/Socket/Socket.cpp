#include "Socket.h"
#include "AuthServer.h"
#include <iostream>

using namespace std;

Socket::Socket(int port)
{
}
Socket::Socket(SOCKET s)
{
	sock = s;
}
Socket::~Socket()
{
	closesocket(sock);
}
SOCKET	Socket::getSocket()
{
	return sock;
}
int		Socket::Create(bool isUdp)
{
	udp = isUdp;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	if (udp == false)
	{
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}
		sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (sock == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}
	}
	else
	{
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock == INVALID_SOCKET)
		{
			fprintf(stderr, "Could not create socket.\n");
			WSACleanup();
			return 1;
		}
		memset((void *)&ClientAddr, '\0', sizeof(struct sockaddr_in));
		ClientAddr.sin_family = AF_INET;
		ClientAddr.sin_addr.s_addr = INADDR_ANY;
		ClientAddr.sin_port = htons(7777);
	}
	return sock;
}
int		Socket::Bind()
{
	if (udp == false)
	{
		iResult = ::bind(sock, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(sock);
			WSACleanup();
			return 1;
		}
	}
	else
	{
		iResult = ::bind(sock, (SOCKADDR*)&ClientAddr, sizeof(ClientAddr));
		if (iResult == SOCKET_ERROR)
		{
			cerr << "ServerSocket: Failed to connect\n";
			system("pause");
			WSACleanup();
			return 1;
		}
	}
	freeaddrinfo(result);
	return 0;
}
int		Socket::Listen()
{
	iResult = listen(sock, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	cout << "Server started on port: " << DEFAULT_PORT << endl;
	return 0;
}
Client	*Socket::Accept()
{
	SOCKET NewConnection = -1;
	ClientAddrLen = sizeof(ClientAddr);
	if ((NewConnection = accept(sock, (SOCKADDR *)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)
	{
		cerr << "accept failed with error: " << WSAGetLastError() << endl;;
		closesocket(sock);
		WSACleanup();
		return NULL;
	}
	Client *client = new Client(NewConnection, inet_ntoa(ClientAddr.sin_addr));
	return client;
}
