/*
	Socket_Win32.cpp for project Server_Library
	Created on 4/2/2016
	Update on 4/2/2016 8:12 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/Socket.hpp"
#include	<iostream>

LPFN_ACCEPTEX				Socket::m_lpfnAcceptEx = NULL;
LPFN_CONNECTEX				Socket::m_lpfnConnectEx = NULL;
LPFN_DISCONNECTEX			Socket::m_lpfnDisconnectEx = NULL;
LPFN_GETACCEPTEXSOCKADDRS	Socket::m_lpfnGetAcceptExSockAddrs = NULL;
LPFN_TRANSMITFILE			Socket::m_lpfnTransmitFile = NULL;

Socket::Socket()
{
}

Socket::~Socket()
{
	Close();
}

int Socket::StartUp()
{
	WSADATA wsaData;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		// Winsock DLL 못 찾음
		return WSAGetLastError();
	}

	// Winsock이 2.2를 지원하는지 확인
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return WSAGetLastError();
	}


	// Load MS Winsock Extension API 
	int nResult = LoadExtensionAPI();
	if (0 != nResult)
	{
		WSACleanup();
		return nResult;
	}
	return 0;
}

int Socket::CleanUp()
{
	if (0 != WSACleanup())
		return WSAGetLastError();

	return 0;
}

int Socket::LoadExtensionAPI()
{
	int nResult = 0;

	// AcceptEx Load
	GUID funcAcceptEx = WSAID_ACCEPTEX;
	nResult = LoadExtensionFunction(funcAcceptEx, (LPVOID*)&m_lpfnAcceptEx);
	if (0 != nResult)
		return nResult;

	// ConnectEx Load
	GUID funcConnectEx = WSAID_CONNECTEX;
	nResult = LoadExtensionFunction(funcConnectEx, (LPVOID*)&m_lpfnConnectEx);
	if (0 != nResult)
		return nResult;

	// DisconnectEx
	GUID funcDisconnectEx = WSAID_DISCONNECTEX;
	nResult = LoadExtensionFunction(funcDisconnectEx, (LPVOID*)&m_lpfnDisconnectEx);
	if (0 != nResult)
		return nResult;

	// GetAcceptExAddr
	GUID funcGetAcceptExAddr = WSAID_GETACCEPTEXSOCKADDRS;
	nResult = LoadExtensionFunction(funcGetAcceptExAddr, (LPVOID*)&m_lpfnGetAcceptExSockAddrs);
	if (0 != nResult)
		return nResult;

	// TransmitFile
	GUID funcTransmitFile = WSAID_TRANSMITFILE;
	nResult = LoadExtensionFunction(funcTransmitFile, (LPVOID*)&m_lpfnTransmitFile);
	if (0 != nResult)
		return nResult;

	return 0;
}

int Socket::LoadExtensionFunction(GUID functionID, LPVOID *pFunc)
{
	Socket socket;
	if (0 != socket.Create(Socket::eSOCKET_TCP))
		return WSAGetLastError();

	DWORD dwBytes = 0;
	int nResult = WSAIoctl(socket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&functionID,
		sizeof(GUID),
		pFunc,
		sizeof(LPVOID),
		&dwBytes,
		0,
		0);

	if (0 != nResult)
		return WSAGetLastError();

	return 0;
}

int Socket::Create(int nSocketType)
{
	UNREFERENCED_PARAMETER(nSocketType);

	m_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == m_socket)
		return WSAGetLastError();

	return 0;
}

int Socket::Bind(SockAddr& rSockAddr)
{
	if (0 != bind(m_socket, (struct sockaddr *) rSockAddr, sizeof(struct sockaddr)))
	{
		return WSAGetLastError();
	}

	return 0;
}

int Socket::Listen(int nBackLog)
{
	if (0 != listen(m_socket, nBackLog))
	{
		return WSAGetLastError();
	}
	return 0;
}

int Socket::Close()
{
	if (INVALID_SOCKET == m_socket)
	{
		return 0;
	}
	if (SOCKET_ERROR == closesocket(m_socket))
	{
		return WSAGetLastError();
	}
	m_socket = INVALID_SOCKET;
	return 0;
}

int Socket::Shutdown(int how)
{
	if (INVALID_SOCKET == m_socket)
	{
		return 0;
	}
	if (SOCKET_ERROR == shutdown(m_socket, how))
	{
		return WSAGetLastError();
	}
	return 0;
}

int Socket::GetPeerName(std::string & rAddress, WORD & rPort)
{
	struct sockaddr_in sockAddr;
	int nSockAddrLen = sizeof(sockAddr);

	if (0 != getpeername(m_socket, (struct sockaddr*) &sockAddr, &nSockAddrLen))
	{
		return WSAGetLastError();
	}
	rAddress = inet_ntoa(sockAddr.sin_addr);
	rPort = ntohs(sockAddr.sin_port);
	return 0;
}

int Socket::GetLocalName(std::string & rAddress, WORD & rPort)
{
	struct sockaddr_in sockAddr;
	int nSockAddrLen = sizeof(sockAddr);

	if (0 != getsockname(m_socket, (struct sockaddr*) &sockAddr, &nSockAddrLen))
	{
		return WSAGetLastError();
	}

	rAddress = inet_ntoa(sockAddr.sin_addr);
	rPort = ntohs(sockAddr.sin_port);

	return 0;
}

int Socket::GetPeerAddr(SockAddr & rAddr)
{
	struct sockaddr_in sockAddr;
	int nSockAddrLen = sizeof(sockAddr);

	if (0 != getpeername(m_socket, (struct sockaddr*) &sockAddr, &nSockAddrLen))
	{
		return WSAGetLastError();
	}

	rAddr.SetSockAddr(inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port));

	return 0;
}

int Socket::GetLocalAddr(SockAddr & rAddr)
{
	struct sockaddr_in sockAddr;
	int nSockAddrLen = sizeof(sockAddr);

	if (0 != getsockname(m_socket, (struct sockaddr*) &sockAddr, &nSockAddrLen))
	{
		return WSAGetLastError();
	}

	rAddr.SetSockAddr(inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port));

	return 0;
}

int Socket::SetNonBlocking(BOOL bActive)
{
	unsigned long i = bActive;
	int result = ioctlsocket(m_socket, FIONBIO, &i);

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetReuseAddr(BOOL bActive)
{
	int result = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&bActive, sizeof(bActive));

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetLinger(BOOL bActive, WORD wTime)
{
	struct linger so_linger;

	so_linger.l_onoff = (u_short)bActive;
	so_linger.l_linger = wTime;

	int result = setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char *)&so_linger, sizeof(so_linger));

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetTCPNoDelay(BOOL bActive)
{
	int result = setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (char*)&bActive, sizeof(bActive));

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetKeepAlive(BOOL bActive)
{
	int result = setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bActive, sizeof(bActive));

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetKeepAlive(DWORD dwKeepAliveTime, DWORD dwKeepAliveInterval)
{
	tcp_keepalive keepAlive = { TRUE, dwKeepAliveTime, dwKeepAliveInterval };

	DWORD dwBytesReturned;
	int result = WSAIoctl(m_socket, SIO_KEEPALIVE_VALS, &keepAlive, sizeof(keepAlive), 0, 0, &dwBytesReturned, NULL, NULL);

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::SetConditionalAccept(BOOL bActive)
{
	int result = setsockopt(m_socket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&bActive, sizeof(bActive));

	if (SOCKET_ERROR == result)
		return WSAGetLastError();

	return 0;
}

int Socket::GetCurReadSocketBuffer()
{
	unsigned long nRead = 0;

	ioctlsocket(m_socket, FIONREAD, &nRead);

	return nRead;
}

int Socket::Connect(struct sockaddr_in * sockaddr)
{
	int rc = connect(m_socket, (struct sockaddr *)sockaddr, sizeof(struct sockaddr_in));
	if (SOCKET_ERROR == rc)
	{
		rc = WSAGetLastError();
		return rc;
	}

	return 0;
}

int Socket::SendStream(unsigned char *pSendBuffer, int nSendSize, bool bSendOut)
{
	int nResult = 0;
	bool bProcess = true;
	BYTE * pBuffer = pSendBuffer;

	if (bSendOut)
	{
		while (bProcess)
		{
			nResult = send(m_socket, (const char *)pBuffer, nSendSize, 0);

			if (SOCKET_ERROR == nResult)
			{
				bProcess = false;
				return SOCKET_ERROR;
			}
			else if (nResult < nSendSize)
			{
				pBuffer += nResult;
				nSendSize -= nResult;

				bProcess = true;
			}
			else
			{
				bProcess = false;
			}
		}
	}
	else
	{
		nResult = send(m_socket, (const char *)pBuffer, nSendSize, 0);

		if (SOCKET_ERROR == nResult)
		{
			return SOCKET_ERROR;
		}
	}

	return nResult;
}

int Socket::RecvStream(BYTE * pRecvBuffer, int nRecvSize)
{
	return recv(m_socket, (char *)pRecvBuffer, nRecvSize, 0);
}
