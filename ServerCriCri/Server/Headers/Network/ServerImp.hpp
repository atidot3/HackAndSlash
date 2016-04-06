/*
	ServerImp.hpp for project Server_Library
	Created on 8/2/2016
	Update on 8/2/2016 11:15 AM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SERVERIMP_HPP_
# define	SERVERIMP_HPP_

/*
	Defines the include and the typedef for Windows and Linux
*/

# ifdef		WIN32

#  include	<winsock2.h>
#  include	<Ws2tcpip.h>
#  pragma	comment(lib, "ws2_32.lib")

# elif		__linux__

#  include	<sys/types.h>
#  include	<sys/socket.h>
#  include	<netinet/in.h>
#  include	<arpa/inet.h>
#  include	<unistd.h>
#  include	<netdb.h>

#  define	INVALID_SOCKET			-1
#  define	SOCKET_ERROR			-1
#  define	closesocket(s)			close(s)

typedef int		SOCKET;
typedef struct sockaddr_in	SOCKADDR_IN;
typedef struct sockaddr		SOCKADDR;
typedef struct in_addr		IN_ADDR;

# else

#  error	"System is not supported!"

# endif

#endif // !SERVERIMP_HPP_

