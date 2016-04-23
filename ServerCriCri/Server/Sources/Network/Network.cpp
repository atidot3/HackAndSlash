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
	listener_state.iomode = IOMODE_ACCEPT;
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
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if (NULL == m_hIOCP)
	{
		return GetLastError();
	}
	return 0;
}
int Network::PostAccept()
{
	DWORD dwBytes;

	listener_state.Reset();
	listener_state.Clear();
	listener_state.iomode = IOMODE_ACCEPT;
	listener_state.wsabuf.buf = new char[1024];
	listener_state.wsabuf.len = 0;
	acceptSocket.Create();

	int rc = listenSocket.AcceptEx(acceptSocket,
		listener_state.wsabuf.buf,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&dwBytes,
		&listener_state);
	if (rc != 0)
		std::cout << "PostAccept failed : "<< GetLastError() << std::endl;
	return rc;
}
Socket	*Network::CompleteAccept(DWORD dwTransferedBytes)
{
	UNREFERENCED_PARAMETER(dwTransferedBytes);

	SOCKADDR_IN * pLocalAddr = NULL;
	SOCKADDR_IN * pRemoteAddr = NULL;
	int nLocalAddrLen = 0;
	int nRemoteAddrLen = 0;

	listenSocket.GetAcceptExSockaddrs(listener_state.wsabuf.buf,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		(SOCKADDR**)&pLocalAddr,
		&nLocalAddrLen,
		(SOCKADDR**)&pRemoteAddr,
		&nRemoteAddrLen);
	std::cout << "SOCKET = " << listenSocket.GetRawSocket() << " SOCKET 2 = " << acceptSocket.GetRawSocket() << std::endl;
	//SetAddress(pLocalAddr, pRemoteAddr);
	ZeroMemory(listener_state.wsabuf.buf, sizeof(SOCKADDR_IN) + 16 + sizeof(SOCKADDR_IN) + 16);
	return &acceptSocket;
}
int Network::CompleteIO(sIOCONTEXT * pIOContext, DWORD dwParam)
{
	return 0;
}
int Network::PostRecv()
{
	return 0;
}