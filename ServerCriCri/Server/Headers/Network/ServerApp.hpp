/*
	ServerApp.hpp for project Server_Library
	Created on 6/2/2016
	Update on 6/2/2016 3:51 PM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SERVERAPP_HPP_
# define	SERVERAPP_HPP_

# include	"Network/Socket.hpp"
# include	"Network/Select.hpp"
#include	"Client.h"
#include	"ClientManager.h"
# include	<list>
# include	<queue>
# include	<atomic>
# include	<iostream>

typedef	std::list<Socket>::iterator	iterator;

struct sSERVERCONFIG
{
	std::string				strClientAcceptAddr;
	WORD					wClientAcceptPort;
	std::string				ExternalIP;
	std::string				Host;
	std::string				User;
	std::string				Password;
	std::string				Database;
	bool					SaveOnLogout;
	unsigned long			PlayerLimits;
	unsigned long			saveInterval;
	int						realmid;
};

class ServerApp
{
private:
	Socket					_server;
	Select					_select;
	std::list<Socket>		_list;
	ClientManager			*cmanager;
	bool					_isRunning;
	std::list<std::string>	_srvCmdList;
# ifdef		WIN32
	WSADATA					_data;
# endif
protected:
	std::queue<std::string>	_wqueue;
	sSERVERCONFIG			m_config;
public:
	ServerApp();
	virtual ~ServerApp();
	void					run();
	int						OnConfiguration(const char * lpszConfigFile); // Load ini file
private:
	void					WSAinit(); // Init Windows Sockets
	void					WSAClose(); // Stop Windows Sockets
	void					consoleIO(); // Get Input from console
protected:
	virtual int				init() = 0;
	virtual void			serverRun() = 0;
	void					addServerCmd(std::string const &cmd) { _srvCmdList.push_back(cmd); }
	bool					isRunning() const { return _isRunning; }
};

#endif // !SERVERAPP_HPP_
