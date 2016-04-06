/*
	ServerApp.hpp for project Server_Library
	Created on 6/2/2016
	Update on 6/2/2016 3:51 PM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SERVERAPP_HPP_
# define	SERVERAPP_HPP_

# include	"Utils/Logger.hpp"
# include	"Network/Socket.hpp"
# include	"Network/Select.hpp"
# include	"Client.h"
# include	"ClientManager.h"
# include	<list>
# include	<queue>
# include	<atomic>
# include	<iostream>

// Get rid of that, that's not clean
typedef	std::list<Socket>::iterator	iterator;

// Create a file for that shit !
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

// Abstract Class for a basic server. Handles Socket I/O and Console I/O
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
	// Constructor
	ServerApp();
	//Destructor
	virtual ~ServerApp();
	// Main loop for the server
	void					run();
	// Load ini file
	int						OnConfiguration(const char * lpszConfigFile);
private:
	// Init Windows Sockets
	void					WSAinit();
	// Stop Windows Sockets
	void					WSAClose();
	// Get Input from console
	void					consoleIO();
protected:
	// User initialization
	virtual int				init() = 0;
	// User Server update loop
	virtual void			serverRun() = 0;
	// Not implemented
	void					addServerCmd(std::string const &cmd) { _srvCmdList.push_back(cmd); }
	// Check if the main server loop is active
	bool					isRunning() const { return _isRunning; }
};

#endif // !SERVERAPP_HPP_
