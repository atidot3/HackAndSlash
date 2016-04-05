/*
	Socket_Win32.cpp for project Server_Library
	Created on 4/2/2016
	Update on 4/2/2016 8:12 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/Socket.hpp"
#include	<iostream>

Socket::Socket()
{
	_type = NONE;
	_state = INACTIVE;
}

Socket::Socket(unsigned int &port)
{
	_type = SERVER;
	_state = INACTIVE;
	_sin.sin_addr.s_addr = INADDR_ANY;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	_state = ACTIVE;
}

Socket::Socket(char const *addr, unsigned int &port)
{
	IN_ADDR	sin_addr;

	_type = CLIENT;
	_state = INACTIVE;
	_addr = *addr;
	inet_pton(AF_INET, addr, &sin_addr);
	_sin.sin_addr = sin_addr;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		std::cerr << WSAGetLastError() << std::endl;
	_state = ACTIVE;
}

Socket::Socket(SOCKET &sock, SOCKADDR_IN &sin)
{
	_type = CLIENT;
	_state = ACTIVE;
	_sin = sin;
	_sock = sock;
}

Socket::~Socket()
{
	this->Close();
}

Socket	&Socket::operator=(Socket &cpy)
{
	std::cerr << "Socket Copied" << std::endl;
	_type = cpy._type;
	_state = cpy._state;
	_sin = cpy._sin;
	_sock = cpy._sock;
	_addr = cpy._addr;

	cpy.setState(INACTIVE);
	return *this;
}

int		Socket::init(unsigned int &port)
{
	if (_state != INACTIVE)
		return 0;
	_type = SERVER;
	_state = INACTIVE;
	_sin.sin_addr.s_addr = INADDR_ANY;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cerr << WSAGetLastError() << std::endl;
		return -1;
	}
	_state = ACTIVE;
	return 0;
}

int		Socket::init(unsigned int &port, const char *addr)
{
	IN_ADDR	sin_addr;

	if (_state != INACTIVE)
		return 0;
	_type = CLIENT;
	_state = INACTIVE;
	inet_pton(AF_INET, addr, &sin_addr);
	_sin.sin_addr = sin_addr;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cerr << WSAGetLastError() << std::endl;
		return -1;
	}
	_state = ACTIVE;
	return 0;
}

int		Socket::Bind()
{
	if (_type != SERVER)
		return 0;
	if (bind(_sock, (SOCKADDR *)&_sin, sizeof _sin) == SOCKET_ERROR)
	{
		perror("bind()");
		return -1;
	}
	return 0;
}

int		Socket::Listen()
{
	if (_type != SERVER)
		return 0;
	if (listen(_sock, 5) == SOCKET_ERROR)
	{
		perror("listen()");
		return -1;
	}
	return 0;
}

int		Socket::Connect()
{
	if (_type != CLIENT || _state == CONNECTED)
		return 0;
	if (connect(_sock, (SOCKADDR *)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		std::cerr << WSAGetLastError() << std::endl;
		return -1;
	}
	return 0;
}

Socket		Socket::Accept()
{
	if (_type != SERVER || _state == INACTIVE)
		return Socket();
	SOCKADDR_IN	c_sin;
	SOCKET		c_sock;
	int			c_sin_size = sizeof(c_sin);

	c_sock = accept(_sock, (SOCKADDR *)&c_sin, &c_sin_size);
	if (c_sock == INVALID_SOCKET)
	{
//		perror("accept()");
		return Socket();
	}
	return Socket(c_sock, c_sin);
}

int		Socket::Close()
{
	if (_state == INACTIVE)
		return 0;
	_state = INACTIVE;
	return closesocket(_sock);
}

int		Socket::Send(Socket &sock, std::string &src)
{
	if (_state == INACTIVE)
		return 0;
	return send(sock._sock, src.c_str(), (int)src.size(), 0);
}

int		Socket::Recv(Socket &sock, std::string &dest)
{
	char	*buff;
	int		res = 0;

	if ((buff = (char *)malloc(1024 * sizeof(*buff))) == NULL)
		return 0;
	if (_state == INACTIVE)
		return 0;
	if ((res = recv(sock._sock, buff, 1024, 0)) < 0)
		std::cerr << "recv err: " << WSAGetLastError() << std::endl;
	else
	{
		buff[res] = 0;
		dest = buff;
	}
	delete buff;
	return res;
}