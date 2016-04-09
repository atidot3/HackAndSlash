#ifndef		ACCEPTOR_HPP_
# define	ACCEPTOR_HPP_

# include	<winsock2.h>
# include	<Ws2tcpip.h>
# include	<mswsock.h>
# pragma	comment(lib, "ws2_32.lib")

# include	"Utils/Logger.hpp"

# define	BUFFER_SIZE		1024

enum Operation
{
	ACCEPT,
	READ,
	WRITE,
	UNKNOWN
};

typedef struct sCompletionKey
{
	SOCKET		socket;
	SOCKADDR_IN	sin;
	Operation	op;
	char		buffer[BUFFER_SIZE];
	int			length;
} CKey;

class Acceptor
{
	CKey			_ck;
	SOCKET			_socket;
	SOCKADDR_IN		_sin;
	HANDLE			_handle;
	LPFN_ACCEPTEX	_lpfnAcceptEx;
	GUID			_guidAcceptEx;
	DWORD			_dwBytes;
	WSAOVERLAPPED	_ovl;

public:
	Acceptor();
	~Acceptor();

	bool	init();
	void	start();
	void	accept(BOOL result, int length, CKey *ck, WSAOVERLAPPED *ovl);

	HANDLE	getHandle() const { return _handle; }
private:

};

#endif // !ACCEPTOR_HPP_
