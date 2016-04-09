#ifndef IOCPSERVER_H
#define IOCPSERVER_H

# include	<winsock2.h>
# include	<Ws2tcpip.h>
# include	<mswsock.h>
# pragma	comment(lib, "ws2_32.lib")

# include	"Utils/Logger.hpp"

# define	MAX_BUF  1024
# define	SERVER_ADDRESS  INADDR_LOOPBACK
# define	SERVICE_PORT  12345

enum // socket operations
{
	OP_NONE,
	OP_ACCEPT,
	OP_READ,
	OP_WRITE
};

typedef struct _SocketState // 
{
	char operation;
	SOCKET socket;
	DWORD length;
	char buf[MAX_BUF];
} SocketState;

class IOCPServer
{
public:
	IOCPServer();
	~IOCPServer();

	void start_accepting(void);
	void accept_completed(BOOL, DWORD, SocketState*, WSAOVERLAPPED*);
	void start_reading(SocketState*, WSAOVERLAPPED*);
	void read_completed(BOOL, DWORD, SocketState*, WSAOVERLAPPED*);
	void start_writing(SocketState*, WSAOVERLAPPED*);
	void write_completed(BOOL, DWORD, SocketState*, WSAOVERLAPPED*);

	void bind_listening_socket(void);
	SOCKET create_accepting_socket(void);
	void create_io_completion_port(void);
	void create_listening_socket(void);
	void destroy_connection(SocketState*, WSAOVERLAPPED*);
	BOOL get_completion_status(DWORD*, SocketState**, WSAOVERLAPPED**);
	void init_winsock(void);
	void load_accept_ex(void);
	SocketState* new_socket_state(void);
	WSAOVERLAPPED* new_overlapped(void);
	void prepare_endpoint(struct sockaddr_in*, u_long, u_short);
	void start_listening(void);
private:
	HANDLE cpl_port;
	SOCKET listener;
	SocketState listener_state;
	WSAOVERLAPPED listener_ovl;
	LPFN_ACCEPTEX pfAcceptEx;
	GUID GuidAcceptEx;
};

#endif