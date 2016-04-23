#include "Network.h"

Network::Network()
{

}
Network::~Network()
{

}
int		Network::Create()
{
	addr.Clear();
	addr.SetSockAddr("192.168.1.36", htons(12345));
	int rc = listenSocket.StartUp();
	if (rc != 0)
	{
		std::cout << "listenSocket.StartUp failed" << std::endl;
		return rc;
	}
	return 0;
}
int		Network::CreateListenSocket()
{
	int rc = listenSocket.Create(Socket::eSOCKET_TCP);
	if (rc != 0)
	{
		std::cout << "listenSocket.Create failed" << std::endl;
		return rc;
	}
	listener_state.socket = 0;
	listener_state.operation = IOMODE_ACCEPT;
	if (CreateIoCompletionPort((HANDLE)listenSocket.GetRawSocket(), m_hIOCP, (ULONG_PTR)&listener_state, 0) != m_hIOCP)
	{
		int err = WSAGetLastError();
		printf("* error %d in listener\n", err);
		return err;
	}
	return 0;
}
int		Network::Listen()
{
	int rc = listenSocket.Bind(addr);
	if (rc != 0)
	{
		std::cout << "listenSocket.Bind failed" << std::endl;
		return rc;
	}
	std::cout << "Bind socket to: " << addr.GetDottedAddr() << " " << addr.GetPort() << std::endl;
	rc = listenSocket.SetReuseAddr(TRUE);
	if (rc != 0)
	{
		std::cout << "listenSocket.SetReuseAddr failed" << std::endl;
		return rc;
	}
	rc = listenSocket.Listen();
	if (rc != 0)
	{
		std::cout << "listenSocket.Listen failed" << std::endl;
		return rc;
	}
	return 0;
}
int Network::CreateIOCP()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == m_hIOCP)
	{
		return GetLastError();
	}
	return 0;
}
int Network::PostAccept()
{
	DWORD dwBytes;
	memset(&listener_ovl, 0, sizeof(WSAOVERLAPPED));
	acceptSocket.Create();

	int rc = listenSocket.AcceptEx(acceptSocket,
		listener_state.buf,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&dwBytes,
		&listener_ovl);
	if (rc != 0)
		std::cout << "PostAccept failed" << std::endl;
	return rc;
}
int Network::CompleteIO(SocketState * pIOContext, DWORD dwParam)
{
	switch (pIOContext->operation)
	{
	case IOMODE_ACCEPT:
	{
		std::cout << "ACCEPT PENDING" << std::endl;
		//return CompleteAccept(dwParam);
		return 0;
	}
	case IOMODE_CONNECT:
	{
		std::cout << "CONNECT PENDING" << std::endl;
		//return CompleteConnect(dwParam);
		return 0;
	}
	case IOMODE_RECV:
	{
		std::cout << "RECV PENDING" << std::endl;
		//return CompleteRecv(dwParam);
		return 0;
	}
	case IOMODE_SEND:
	{
		std::cout << "SEND PENDING" << std::endl;
		//return CompleteSend(dwParam);
		return 0;
	}
	default:
		return -1;
	}
	return 0;
}