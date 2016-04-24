#include "Connection.h"

Connection::Connection()
{
	std::cout << "Client accepted ?" << std::endl;
	//SetStatus(STATUS_ACTIVE);
	//m_dwConnectTime = GetTickCount();
	//m_bConnected = true;
}
Connection::Connection(Socket *acceptedSocket)
{
	clientSock = acceptedSocket;
}
Connection::~Connection()
{
}
int Connection::PostRecv()
{
	DWORD dwFlags = 0;
	DWORD dwTransferedBytes = 0;
	sIOCONTEXT  listener_state;

	listener_state.Reset();
	listener_state.iomode = IOMODE_RECV;
	listener_state.wsabuf.buf = new char(1024);
	listener_state.wsabuf.len = 1024;


	int rc = clientSock->RecvEx(&listener_state.wsabuf,
		1,
		&dwTransferedBytes,
		&dwFlags,
		&listener_state);
	std::cout << dwTransferedBytes << std::endl;
	if (0 != rc)
	{
		printf("RecvEx Function Failed (%d)", rc);
		return rc;
	}
	return 0;
}