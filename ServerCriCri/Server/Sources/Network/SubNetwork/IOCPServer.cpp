#include "IOCPServer.h"

IOCPServer::IOCPServer()
{
	GuidAcceptEx = WSAID_ACCEPTEX;
}
IOCPServer::~IOCPServer()
{
}
void IOCPServer::start_accepting(void)
{
	SOCKET acceptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (acceptor == INVALID_SOCKET)
	{
		printf("* error creating accept socket!\n");
		system("PAUSE");
		exit(1);
	}
	DWORD expected = sizeof(struct sockaddr_in) + 16;

	printf("* started accepting connections...\n");

	// uses listener's completion key and overlapped structure
	listener_state.socket = acceptor;
	memset(&listener_ovl, 0, sizeof(WSAOVERLAPPED));

	// starts asynchronous accept
	if (!pfAcceptEx(listener, acceptor, listener_state.buf, 0 /* no recv */,
		expected, expected, NULL, &listener_ovl))
	{
		int err = WSAGetLastError();
		if (err != ERROR_IO_PENDING)
		{
			printf("* error %d in AcceptEx\n", err);
			system("PAUSE");
			exit(1);
		}
	}
}
void IOCPServer::accept_completed(BOOL resultOk, DWORD length, SocketState* socketState, WSAOVERLAPPED* ovl)
{
	SocketState* newSocketState;

	if (resultOk)
	{
		printf("* new connection created\n");
		// "updates the context" (whatever that is...)
		setsockopt(socketState->socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
			(char *)&listener, sizeof(listener));

		// associates new socket with completion port
		newSocketState = new_socket_state();
		newSocketState->socket = socketState->socket;
		if (CreateIoCompletionPort((HANDLE)newSocketState->socket, cpl_port,
			(ULONG_PTR)newSocketState, 0) != cpl_port)
		{
			int err = WSAGetLastError();
			printf("* error %d in CreateIoCompletionPort in line %d\n", err, __LINE__);
			system("PAUSE");
		}
		start_reading(newSocketState, new_overlapped());
		start_accepting();
	}

	else
	{
		int err = GetLastError();
		printf("* error (%d,%d) in accept, cleaning up and retrying!!!", err, length);
		closesocket(socketState->socket);
		start_accepting();
	}
}
void IOCPServer::start_reading(SocketState* socketState, WSAOVERLAPPED* ovl)
{
	DWORD flags = 0;
	WSABUF wsabuf = { MAX_BUF, socketState->buf };

	memset(ovl, 0, sizeof(WSAOVERLAPPED));
	socketState->operation = OP_READ;
	if (WSARecv(socketState->socket, &wsabuf, 1, NULL, &flags, ovl, NULL) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
		{
			printf("*error %d in WSARecv\n", err);
			destroy_connection(socketState, ovl);
		}
	}
}
void IOCPServer::read_completed(BOOL resultOk, DWORD length, SocketState* socketState, WSAOVERLAPPED* ovl)
{
	if (resultOk)
	{
		if (length > 0)
		{
			printf("* read operation completed, %d bytes read\n", length);
			// socketState->buf contain stored buffer
			socketState->length = length;
			start_writing(socketState, ovl);
		}
		else
		{
			printf("* connection closed by client\n");
			destroy_connection(socketState, ovl);
		}
	}
	else
	{
		int err = GetLastError();
		// client reset connection
		destroy_connection(socketState, ovl);
	}
}
void IOCPServer::start_writing(SocketState* socketState, WSAOVERLAPPED* ovl)
{
	WSABUF wsabuf = { socketState->length, socketState->buf };

	memset(ovl, 0, sizeof(WSAOVERLAPPED));
	socketState->operation = OP_WRITE;

	if (WSASend(socketState->socket, &wsabuf, 1, NULL, 0, ovl, NULL)
		== SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
		{
			printf("*error %d in WSASend\n", err);
			system("PAUSE");
		}
	}
}
void IOCPServer::write_completed(BOOL resultOk, DWORD length, SocketState* socketState, WSAOVERLAPPED* ovl)
{
	if (resultOk)
	{
		if (length > 0)
		{
			printf("* write operation completed\n");
			start_reading(socketState, ovl);
		}
		else
		{
			printf("* connection closed by client!\n");
			destroy_connection(socketState, ovl);
		}
	}
	else
	{
		int err = GetLastError();
		printf("* error %d on send, assuming connection was reset!\n");
		destroy_connection(socketState, ovl);
	}
}

void IOCPServer::bind_listening_socket(void)
{
	struct sockaddr_in sin;

	prepare_endpoint(&sin, SERVER_ADDRESS, SERVICE_PORT);

	if (bind(listener, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("* error in bind!\n");
		system("PAUSE");
		exit(1);
	}
}

void IOCPServer::create_io_completion_port(void)
{
	cpl_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (!cpl_port)
	{
		int err = WSAGetLastError();
		printf("* error %d in line %d CreateIoCompletionPort\n", err, __LINE__);
		system("PAUSE");
	}
}
void IOCPServer::create_listening_socket(void)
{
	listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listener == INVALID_SOCKET)
	{
		printf("* error creating listening socket!\n");
		system("PAUSE");
		exit(1);
	}

	listener_state.socket = 0;
	listener_state.operation = OP_ACCEPT;

	if (CreateIoCompletionPort((HANDLE)listener, cpl_port, (ULONG_PTR)&listener_state, 0) != cpl_port)
	{
		int err = WSAGetLastError();
		printf("* error %d in listener\n", err);
		system("PAUSE");
		exit(1);
	}
}
void IOCPServer::destroy_connection(SocketState* socketState, WSAOVERLAPPED* ovl)
{
	closesocket(socketState->socket);
	free(socketState);
	free(ovl);
}
BOOL IOCPServer::get_completion_status(DWORD* length, SocketState** socketState, WSAOVERLAPPED** ovl_res)
{
	BOOL resultOk;
	*ovl_res = NULL;
	*socketState = NULL;

	resultOk = GetQueuedCompletionStatus(cpl_port, length, (PULONG_PTR)socketState, ovl_res, INFINITE);
	if (!resultOk)
	{
		DWORD err = GetLastError();
		printf("* error %d getting completion port status!!!\n", err);
		return false;
	}
	if (!*socketState || !*ovl_res)
	{
		printf("* don't know what to do, aborting!!!\n");
		return false;
	}
	return resultOk;
}
void IOCPServer::init_winsock(void)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("* error in WSAStartup!\n");
		exit(1);
	}
}
void IOCPServer::load_accept_ex(void)
{
	DWORD dwBytes;

	WSAIoctl(listener, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx,
		sizeof(GuidAcceptEx), &pfAcceptEx, sizeof(pfAcceptEx), &dwBytes, NULL,
		NULL);
}
SocketState* IOCPServer::new_socket_state(void)
{
	return (SocketState*)calloc(1, sizeof(SocketState));
}
WSAOVERLAPPED* IOCPServer::new_overlapped(void)
{
	return (WSAOVERLAPPED*)calloc(1, sizeof(WSAOVERLAPPED));
}
void IOCPServer::prepare_endpoint(struct sockaddr_in* sin, u_long address, u_short port)
{
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = htonl(address);
	sin->sin_port = htons(port);
}
void IOCPServer::start_listening(void)
{
	if (listen(listener, 100) == SOCKET_ERROR)
	{
		printf("* error in listen!\n");
		system("PAUSE");
		exit(1);
	}
	printf("* started listening for connection requests...\n");
}
