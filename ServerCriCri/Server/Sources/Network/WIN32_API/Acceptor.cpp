#include	"Network/Win32_API/Acceptor.hpp"

Acceptor::Acceptor()
{
}

Acceptor::~Acceptor()
{
}

bool	Acceptor::init()
{
	_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (_handle == NULL)
	{
		LOG("CreateIoCompletionPort error: " + std::to_string(GetLastError()));
		return false;
	}

	_socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
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

	if (bind(_socket, (SOCKADDR *)&_sin, sizeof(_sin)) == SOCKET_ERROR)
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

	if (CreateIoCompletionPort((HANDLE)_socket, _handle, (ULONG_PTR)&_ck, 0) != _handle)
	{
		LOG("CreateIoCompletionPort for socket error: " + std::to_string(GetLastError()));
		return false;
	}

	_guidAcceptEx = WSAID_ACCEPTEX;
	int retval = WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&_guidAcceptEx, sizeof(_guidAcceptEx),
		&_lpfnAcceptEx, sizeof(_lpfnAcceptEx),
		&_dwBytes, NULL, NULL);
	if (retval == SOCKET_ERROR)
	{
		LOG("WSAIoctl error: " + std::to_string(WSAGetLastError()));
		return false;
	}

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

	retval = _lpfnAcceptEx(_socket, newSocket, _ck.buffer, _ck.length - ((sizeof(SOCKADDR_IN) + 16) * 2), sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &_dwBytes, &_ovl);
	if (retval == FALSE)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
			LOG("AcceptEx failed error: " + std::to_string(err));
	}
}

void	Acceptor::accept(BOOL result, int length, CKey *ck, WSAOVERLAPPED *ovl)
{
	CKey	newCKey;
	int		size = sizeof(newCKey.sin);

	if (result)
	{
		if (getsockname(ck->socket, (SOCKADDR*)&newCKey.sin, &size) != 0)
		{
			LOG("Getsockname failed error: " + std::to_string(WSAGetLastError()));
		}

		char		dst[INET_ADDRSTRLEN];
		IN_ADDR		addr = newCKey.sin.sin_addr;
		inet_ntop(newCKey.sin.sin_family, &addr, dst, INET_ADDRSTRLEN);
		std::string	ret = dst;

		LOG("Connection accepted from: " + ret);
		setsockopt(ck->socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)_socket, sizeof(_socket));
		newCKey.socket = ck->socket;
		closesocket(newCKey.socket);
	}
	else
	{
		LOG("AcceptEx error: " + std::to_string(WSAGetLastError()));
		closesocket(ck->socket);
	}

	this->start();
}