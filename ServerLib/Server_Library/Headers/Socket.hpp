/*
	Socket_win32.hpp for project Server_Library
	Created on 4/2/2016
	Update on 4/2/2016 8:23 PM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SOCKET_HPP_
# define	SOCKET_HPP_

# include	"ServerImp.hpp"
# include	<string>

class SERVER_LIBRARY_API Socket
{
public:
	enum TYPE
	{
		NONE = 0,
		CLIENT = 1,
		SERVER = 2
	};

	enum STATE
	{
		INACTIVE = 0,
		ACTIVE = 1,
		CONNECTED = 2
	};

private:
	SOCKET			_sock;
	SOCKADDR_IN		_sin;
	STATE			_state;
	TYPE			_type;

public:
	Socket();
	// Socket for Server
	Socket(unsigned int &port);
	// Socket for Client
	Socket(char const *addr, unsigned int &port);
	// Create socket from accept
	Socket(SOCKET &sock, SOCKADDR_IN &sin);
	~Socket();

	Socket	&operator=(Socket &cpy);

	int		init(unsigned int &port);
	int		init(unsigned int &port, char const *addr);

	int		Bind();
	int		Listen();
	int		Connect();
	Socket	Accept();
	int		Close();

	int		Send(Socket &sock, std::string &src);
	int		Recv(Socket &sock, std::string &dest);

	STATE	getState() const { return _state; }
	SOCKET	getRawSocket() const { return _sock; }

private:
	void	setState(STATE state) { _state = state; }
};

#endif // !SOCKET_HPP_

