#ifndef		SOCKADDR_H_
# define	SOCKADDR_H_

# include	<string>
#include	<mstcpip.h>
#include	<MSWSock.h>

class SockAddr
{
public:

	SockAddr()
		:m_bInit(false) {
		memset(&m_sockAddr, 0x00, sizeof(m_sockAddr));
	}
	SockAddr(unsigned long addr, unsigned short port)
		:m_bInit(false)
	{
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = port;
		m_sockAddr.sin_addr.s_addr = addr;
	}
	SockAddr(const char * addr, unsigned short port)
		:m_bInit(false)
	{
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = port;

		struct hostent *remoteHost;
		remoteHost = gethostbyname(addr);
		if (NULL == remoteHost)
		{
			m_sockAddr.sin_addr.s_addr = inet_addr(addr);
		}
		else
		{
			m_sockAddr.sin_addr.s_addr = *(u_long*)remoteHost->h_addr_list[0];
		}
	}


	SockAddr(const SockAddr & sockAddr)
		:m_sockAddr(sockAddr.m_sockAddr), m_bInit(false) {}


	SockAddr(const sockaddr & sockAddr)
		:m_sockAddr(*(sockaddr_in*)&sockAddr), m_bInit(false) {}


	SockAddr(const sockaddr_in & sockAddr)
		:m_sockAddr(sockAddr), m_bInit(false) {}


	~SockAddr() {}



public:
	void SetSockAddr(const char * addr, unsigned short port)
	{
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = port;
		m_sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	}
	void Clear()
	{
		memset(&m_sockAddr, '\0', sizeof(sockaddr_in));
		m_bInit = false;
		m_strAddr.clear();
	}
	unsigned short GetPort() const
	{
		return ntohs(m_sockAddr.sin_port);
	}
	void SetPort(const unsigned short port)
	{
		m_sockAddr.sin_port = htons(port);
	}
	unsigned int GetAddr() const
	{
		return m_sockAddr.sin_addr.s_addr;
	}
	const char * GetDottedAddr()
	{
		if (!m_bInit)
		{
			m_strAddr = InetNtoA();
			m_bInit = true;
		}

		return m_strAddr.c_str();
	}
	void SetAddr(const unsigned int addr)
	{
		m_sockAddr.sin_addr.s_addr = htonl(addr);
	}
	const char * InetNtoA()
	{
		return inet_ntoa(m_sockAddr.sin_addr);
	}
	SockAddr & operator=(const SockAddr & rhs)
	{
		if (this != &rhs)
		{
			m_sockAddr = rhs.m_sockAddr;
			m_bInit = rhs.m_bInit;
			m_strAddr = rhs.m_strAddr;
		}

		return *this;
	}
	SockAddr & operator=(sockaddr & sockAddr)
	{
		m_sockAddr = *(sockaddr_in*)&sockAddr;
		m_bInit = false;
		m_strAddr.clear();

		return *this;
	}
	SockAddr & operator=(sockaddr_in & sockAddr)
	{
		m_sockAddr = sockAddr;
		m_bInit = false;
		m_strAddr.clear();

		return *this;
	}
	operator sockaddr()
	{
		return *((sockaddr *)&m_sockAddr);
	}
	operator sockaddr_in()
	{
		return *((sockaddr_in *)&m_sockAddr);
	}
	operator sockaddr*()
	{
		return (sockaddr *)&m_sockAddr;
	}
	operator sockaddr_in*()
	{
		return (sockaddr_in *)&m_sockAddr;
	}
	//operator SOCKADDR() { return *((sockaddr *)&m_sockAddr); }
	//operator SOCKADDR_IN() { return *((sockaddr_in *)&m_sockAddr); }
private:
	sockaddr_in m_sockAddr;	// real socket address
	std::string	m_strAddr;
	bool		m_bInit;
};

#endif /*SOCKADDR_H_*/