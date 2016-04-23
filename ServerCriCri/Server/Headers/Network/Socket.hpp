/*
	Socket_win32.hpp for project Server_Library
	Created on 4/2/2016
	Update on 4/2/2016 8:23 PM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SOCKET_HPP_
# define	SOCKET_HPP_

# include	"ServerImp.hpp"
#include	"SockAddr.h"

// Base Socket Class. Handles TCP Socket Only for now
class Socket
{
public:
	// Type of socket
	enum TYPE
	{
		NONE = 0,
		CLIENT = 1, // Client Socket
		SERVER = 2	// Server Socket
	};
	enum
	{
		eSOCKET_TCP = 0,
		eSOCKET_UDP,
	};

private:
	SOCKET			_sock;
	SOCKADDR_IN		_sin;
	TYPE			_type;

public:
	/*
		Constructor for a Server socket
		@param &port:	The port on which the server will listen to
	*/
	Socket();
	// Destructor
	virtual ~Socket();

	static int							StartUp();

	static int							CleanUp();
protected:
	static int							LoadExtensionAPI();
	static int							LoadExtensionFunction(GUID functionID, LPVOID *pFunc);
public:
	int									Create(int nSocketType = 0);
	int									Bind(SockAddr& rSockAddr);
	int									Listen(int nBackLog = SOMAXCONN);
	int									Close();
	int									Shutdown(int how);
	int									Connect(struct sockaddr_in * sockaddr);
	int									SendStream(BYTE * pSendBuffer, int nSendSize, bool bSendOut);
	int									RecvStream(BYTE * pRecvBuffer, int nRecvSize);
	int									AcceptEx(Socket &rAcceptSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped);
	int									ConnectEx(const struct sockaddr* name, int namelen, PVOID lpSendBuffer, DWORD dwSendDataLength, LPDWORD lpdwBytesSent, LPOVERLAPPED lpOverlapped);
	int									DisconnectEx(LPOVERLAPPED lpOverlapped, DWORD dwFlags, DWORD reserved);
	void								GetAcceptExSockaddrs(PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPSOCKADDR* LocalSockaddr, LPINT LocalSockaddrLength, LPSOCKADDR* RemoteSockaddr, LPINT RemoteSockaddrLength);
	int									RecvEx(LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped);
	int									SendEx(LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped);
	void								Attach(SOCKET socket) { m_socket = socket; }
	void								Detach() { m_socket = INVALID_SOCKET; }
	int									GetPeerName(std::string & rAddress, WORD & rPort);
	int									GetLocalName(std::string & rAddress, WORD & rPort);
	int									GetPeerAddr(SockAddr & rAddr);
	int									GetLocalAddr(SockAddr & rAddr);
	SOCKET								GetRawSocket() { return m_socket; }
	bool								IsCreated() { return INVALID_SOCKET != m_socket; }
	operator SOCKET() { return *((SOCKET *)&m_socket); }
	Socket &							operator=(const Socket & rhs);
public:
	int									SetOption(DWORD dwSockOption);
	int									SetNonBlocking(BOOL bActive);
	int									SetReuseAddr(BOOL bActive);
	int									SetLinger(BOOL bActive, WORD wTime);
	int									SetTCPNoDelay(BOOL bActive);
	int									SetKeepAlive(BOOL bActive);
	int									SetKeepAlive(DWORD dwKeepAliveTime, DWORD dwKeepAliveInterval);
	int									SetConditionalAccept(BOOL bActive);
	int									GetCurReadSocketBuffer();
protected:
	SOCKET								m_socket;
	static LPFN_ACCEPTEX				m_lpfnAcceptEx;
	static LPFN_CONNECTEX				m_lpfnConnectEx;
	static LPFN_DISCONNECTEX			m_lpfnDisconnectEx;
	static LPFN_GETACCEPTEXSOCKADDRS	m_lpfnGetAcceptExSockAddrs;
	static LPFN_TRANSMITFILE			m_lpfnTransmitFile;

	sockaddr_in m_sockAddr;	// real socket address
	std::string	m_strAddr;
};


inline int Socket::AcceptEx(Socket &rAcceptSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped)
{
	if (!m_lpfnAcceptEx(m_socket, rAcceptSocket.GetRawSocket(), lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength, lpdwBytesReceived, lpOverlapped))
	{
		int rc = WSAGetLastError();
		if (ERROR_IO_PENDING != rc)
		{
			return rc;
		}
	}
	return 0;
}

inline int Socket::ConnectEx(const struct sockaddr* name, int namelen, PVOID lpSendBuffer, DWORD dwSendDataLength, LPDWORD lpdwBytesSent, LPOVERLAPPED lpOverlapped)
{
	if (!m_lpfnConnectEx(m_socket, name, namelen, lpSendBuffer, dwSendDataLength, lpdwBytesSent, lpOverlapped))
	{
		int rc = WSAGetLastError();
		if (ERROR_IO_PENDING != rc)
		{
			return rc;
		}
	}
	return 0;
}

inline int Socket::DisconnectEx(LPOVERLAPPED lpOverlapped, DWORD dwFlags, DWORD reserved)
{
	if (!m_lpfnDisconnectEx(m_socket, lpOverlapped, dwFlags, reserved))
	{
		int rc = WSAGetLastError();
		if (ERROR_IO_PENDING != rc)
		{
			return rc;
		}
	}
	return 0;
}

inline void Socket::GetAcceptExSockaddrs(PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPSOCKADDR* LocalSockaddr, LPINT LocalSockaddrLength, LPSOCKADDR* RemoteSockaddr, LPINT RemoteSockaddrLength)
{
	m_lpfnGetAcceptExSockAddrs(lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength, LocalSockaddr, LocalSockaddrLength, RemoteSockaddr, RemoteSockaddrLength);
}

inline int Socket::RecvEx(LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped)
{
	if (0 != ::WSARecv(m_socket, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, NULL))
	{
		int rc = WSAGetLastError();
		if (ERROR_IO_PENDING != rc)
		{
			return rc;
		}
	}
	return 0;
}

inline int Socket::SendEx(LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped)
{
	if (0 != ::WSASend(m_socket, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, NULL))
	{
		int rc = WSAGetLastError();
		if (ERROR_IO_PENDING != rc)
		{
			return rc;
		}
	}

	return 0;
}

inline Socket & Socket::operator=(const Socket & rhs)
{
	m_socket = rhs.m_socket;
	return *this;
}


#endif // !SOCKET_HPP_
