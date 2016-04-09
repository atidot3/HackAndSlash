#include	"Network/Win32_API/Acceptor.hpp"

Acceptor::Acceptor()
{
}

Acceptor::~Acceptor()
{
}

static WSAOVERLAPPED* new_overlapped(void)
{
	return (WSAOVERLAPPED*)calloc(1, sizeof(WSAOVERLAPPED));
}

void	Acceptor::read(CKey *ck, WSAOVERLAPPED *ovl)
{
	DWORD flags = 0;
	WSABUF wsabuf = { BUFFER_SIZE, ck->buffer };

	memset(ovl, 0, sizeof(WSAOVERLAPPED));
	ck->op = Operation::READ;
	if (WSARecv(ck->socket, &wsabuf, 1, NULL, &flags, ovl, NULL) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
		{
			printf("*error %d in WSARecv\n", err);
			closesocket(ck->socket);
			return;
		}
	}
	std::cout << wsabuf.buf << std::endl;
}

void	Acceptor::read_completed(BOOL result, int length, CKey *ck, WSAOVERLAPPED *ovl)
{
	if (result)
	{
		if (length > 0)
		{
			printf("* read operation completed, %d bytes read\n", length);

			// starts another write
			ck->length = length;
			//start_writing(socketState, ovl);
		}
		else // length == 0
		{
			printf("* connection closed by client\n");
			closesocket(ck->socket);
		}
	}
	else // !resultOk, assumes connection was reset
	{
		int err = GetLastError();
		printf("* error %d in recv, assuming connection was reset by client\n",
			err);
		closesocket(ck->socket);
	}
}

bool	Acceptor::init()
{
	_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0); // initialize input / output (FD controller)
	if (_handle == NULL)
	{
		LOG("CreateIoCompletionPort error: " + std::to_string(GetLastError()));
		return false;
	}
	_socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED); //(Create the socket...)
	if (_socket == INVALID_SOCKET)
	{
		LOG("Socket error: " + std::to_string(WSAGetLastError()));
		return false;
	}
	_ck.socket = _socket;
	_ck.op = Operation::ACCEPT;

	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	_sin.sin_port = htons(12345);

	if (bind(_socket, (SOCKADDR *)&_sin, sizeof(_sin)) == SOCKET_ERROR) // bind...
	{
		LOG("Bind error: " + std::to_string(WSAGetLastError()));
		return false;
	}
	_ck.sin = _sin;

	if (listen(_socket, 8) == SOCKET_ERROR)
	{
		LOG("Listen error: " + std::to_string(WSAGetLastError()));
		return false;
	}

	if (CreateIoCompletionPort((HANDLE)_socket, _handle, (ULONG_PTR)&_ck, 0) != _handle) // link server socket to controller
	{
		LOG("CreateIoCompletionPort for socket error: " + std::to_string(GetLastError()));
		return false;
	}

	_guidAcceptEx = WSAID_ACCEPTEX;
	int retval = WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&_guidAcceptEx, sizeof(_guidAcceptEx),
		&_lpfnAcceptEx, sizeof(_lpfnAcceptEx),
		&_dwBytes, NULL, NULL); // non bloquant accept function
	if (retval == SOCKET_ERROR)
	{
		LOG("WSAIoctl error: " + std::to_string(WSAGetLastError()));
		return false;
	}

	_guidGetSocketaddr = WSAID_GETACCEPTEXSOCKADDRS;
	retval = WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&_guidGetSocketaddr, sizeof(_guidGetSocketaddr),
		&_lpfnGetSockaddr, sizeof(_lpfnGetSockaddr),
		&_dwBytes2, NULL, NULL);
	if (retval == SOCKET_ERROR)
	{
		LOG("WSAIoctl2 error: " + std::to_string(WSAGetLastError()));
		return false;
	}

	/*_guidGetWsaRECV = WSAID_WSARECVMSG;
	retval = WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&_guidGetWsaRECV, sizeof(_guidGetWsaRECV),
		&_lpfnWsaRecvMsg, sizeof(_lpfnWsaRecvMsg),
		&_dwBytes3, NULL, NULL);
	if (retval == SOCKET_ERROR)
	{
		LOG("WSAIoctl2 error: " + std::to_string(WSAGetLastError()));
		return false;
	}*/

	return true;
}

void	Acceptor::start()
{
	SOCKET	newSocket;
	int		retval = 0;

	newSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (newSocket == INVALID_SOCKET)
	{
		LOG("Accept Socket error: " + std::to_string(WSAGetLastError()));
		return;
	}
	_ck.socket = newSocket;
	_ck.length = BUFFER_SIZE;
	memset(&_ovl, 0, sizeof(WSAOVERLAPPED));
	// starts asynchronous accept
	retval = _lpfnAcceptEx(_socket, newSocket, _ck.buffer, _ck.length - ((sizeof(SOCKADDR_IN) + 16) * 2), sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &_dwBytes, &_ovl); // accept windows / remove header
	if (retval == FALSE)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
			LOG("AcceptEx failed error: " + std::to_string(err));
	}
}

void	Acceptor::accept(BOOL result, int length, CKey *ck, WSAOVERLAPPED *ovl)
{
	CKey	*newCKey = new CKey;
	SOCKADDR_IN	*oldSin = &ck->sin, *newSin = new SOCKADDR_IN;
	int		size = sizeof(*newSin);
	int		oldSize = sizeof(*oldSin);
	int		retval = 0;
	
	newSin = NULL;
	if (result)
	{
		_lpfnGetSockaddr(ck->buffer, _ck.length - ((sizeof(SOCKADDR_IN) + 16) * 2), sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, (SOCKADDR**)&newSin, &size, (SOCKADDR**)&oldSin, &oldSize);
		char		dst[INET_ADDRSTRLEN];
		std::string	ret;
		IN_ADDR		addr = newSin->sin_addr;

		inet_ntop(_sin.sin_family, &addr, dst, INET_ADDRSTRLEN);
		ret = dst;
		setsockopt(ck->socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)_socket, sizeof(_socket));
		LOG("Connection accepted from: " + ret);
		newCKey->socket = ck->socket;
		/*
		// associates new socket with completion port
		
		// using newCKey = fucked  //  using ck = showing buffer etc
		WSAMSG wsaMsg;
		WSABUF wsaBufData;
		char szControlBuffer[1024] = "";
		char szDataBuffer[1024] = "";
		DWORD dwBytesRecved = 0;

		wsaBufData.buf = szControlBuffer;
		wsaBufData.len = sizeof(szControlBuffer);
		wsaMsg.name = (sockaddr *)&newCKey->sin;
		wsaMsg.namelen = sizeof(newCKey->sin);
		wsaMsg.lpBuffers = &wsaBufData;
		wsaMsg.dwBufferCount = 1;
		wsaMsg.Control.buf = szControlBuffer;
		wsaMsg.Control.len = sizeof(szControlBuffer);
		wsaMsg.dwFlags = 0;
		_lpfnWsaRecvMsg(newCKey->socket, &wsaMsg, &dwBytesRecved, NULL, NULL);
		if (CreateIoCompletionPort((HANDLE)newCKey->socket, _handle, (ULONG_PTR)newCKey, 0) != _handle)
		{
			int err = WSAGetLastError();
			printf("* error %d in CreateIoCompletionPort in line %d\n", err, __LINE__);  // got error by using non pointeur on newCKey (CKey	*newCKey = new CKey;)
			closesocket(newCKey->socket);
			return;
		}
		// starts receiving from the new connection
		read(newCKey, new_overlapped());
		*/

		closesocket(newCKey->socket);
	}
	else
	{
		LOG("AcceptEx error: " + std::to_string(WSAGetLastError()));
		closesocket(ck->socket);
	}
	
	// starts waiting for another connection request
	this->start();
}