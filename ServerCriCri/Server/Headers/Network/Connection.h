#ifndef		CONNECTION_H_
# define	CONNECTION_H_

#include	"Network.h"

const DWORD CONNECTION_KEEP_ALIVE_CHECK_TIME = 15 * 1000;

class Connection
{
public:
	enum eSTATUS
	{
		STATUS_INIT = 0,			// CONSTRUCTOR
		STATUS_CREATE,				// 
		STATUS_ACCEPT,				// Accept
		STATUS_CONNECT,				// Connect
		STATUS_ACTIVE,				// KEEP ALIVE
		STATUS_CLOSE,				// CLOSE CONNECTION
		STATUS_SHUTDOWN,			// SHUTDOWN SOCKET ETC
		STATUS_DESTROY,				// DESTROY CLASS

		MAX_STATUS
	};

public:
	Connection();
	~Connection();
	void			SetAddress(SOCKADDR_IN * pLocalAddr, SOCKADDR_IN * pRemoteAddr);
	
	int				Create();
	void			Close(bool bForce = false);
	int				Disconnect(bool bGraceful);


private:

	DWORD								m_dwConnectTime;

	DWORD								m_dwBytesRecvSize;
	DWORD								m_dwBytesSendSize;
	DWORD								m_dwBytesRecvSizeMax;
	DWORD								m_dwBytesSendSizeMax;

	DWORD								m_dwPacketRecvCount;
	DWORD								m_dwPacketSendCount;
};

#endif /*CONNECTION_H_*/