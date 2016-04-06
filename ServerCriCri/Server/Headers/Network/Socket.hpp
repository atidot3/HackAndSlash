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

	// State of the socket
	enum STATE
	{
		INACTIVE = 0,
		ACTIVE = 1,
	};

private:
	SOCKET			_sock;
	SOCKADDR_IN		_sin;
	STATE			_state;
	TYPE			_type;

public:
	Socket();
	/*
		Constructor for a Server socket
		@param &port:	The port on which the server will listen to
	*/
	Socket(unsigned int &port);
	/*
		Constructor for a Client socket
		@param *addr:	The IP address on which the client will connect
		@param &port:	The port on which the client will connect
	*/
	Socket(char const *addr, unsigned int &port);
	// Destructor
	~Socket();

	/*
		Assignment Operator for Sockets. The Socket copied is disabled
		@param cpy:	Socket to copy
	*/
	Socket	&operator=(Socket &cpy);

	/*
		Initialization for Server inactive socket
		@param &port:	The port on which the server will listen to
	*/
	int		init(unsigned int &port);
	/*
		Initialization for Client inactive socket
		@param *addr:	The IP address on which the client will connect
		@param &port:	The port on which the client will connect
	*/
	int		init(unsigned int &port, char const *addr);

	/* Bind a Server socket */
	int		Bind();

	/* Make the Server socket listen to the set port */
	int		Listen();

	/* Connect the Client socket to the server */
	int		Connect();

	/*
		Accept a new Socket
		@param &sock:	Socket to be accepted. Will be closed before
	*/
	int		Accept(Socket &sock);

	/* Close a socket and set it as INACTIVE */
	int		Close();

	/*
		Send data to a socket
		@param &sock:	Socket to send data
		@param &src:	Data to send
	*/
	int		Send(Socket &sock, std::string &src);
	/*
		Receive data from a socket
		@param &sock:	Socket from which to receive data
		@param &dest:	Received data
	*/
	int		Recv(Socket &sock, std::string &dest);

	// Return the state of the socket
	STATE	getState() const { return _state; }
	// Return the raw socket of the class (Should be private or protected)
	SOCKET	getRawSocket() const { return _sock; }
	// Return the IP address of the Client
	std::string	getAddr();

private:
	// Create socket from accept
	Socket(SOCKET &sock, SOCKADDR_IN &sin);

	/*
		Set the socket state
		@param state:	State to be set
	*/
	void	setState(STATE state) { _state = state; }
};

#endif // !SOCKET_HPP_

