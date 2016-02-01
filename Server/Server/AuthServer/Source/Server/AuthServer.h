#ifndef _AUTHSERVER_H_
# define _AUTHSERVER_H_

#pragma once

#include <mutex>
#include "NtlSfx.h"
#include "../Client/Client.h"
#include "../Game/Groupe/Groupe.h"
#include "../Game/Session/Session.h"
#include "NtlPacketEncoder_RandKey.h"
#include "mysqlconn_wrapper.h"
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client;

enum APP_LOG
{
	PRINT_LOG = 0,
	PRINT_APP = 1,
	PRINT_ERROR = 2
};
enum AUTH_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
};
struct sSERVERCONFIG
{
	CNtlString		strClientAcceptAddr;
	WORD			wClientAcceptPort;
	CNtlString		ExternalIP;
	CNtlString		Host;
	CNtlString		User;
	CNtlString		Password;
	CNtlString		Database;
	DWORD			SaveOnLogout;
	DWORD			PlayerLimits;
	DWORD			saveInterval;
};

const DWORD					MAX_NUMOF_GAME_CLIENT = 100;
const DWORD					MAX_NUMOF_SERVER = 1;
const DWORD					MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class CAuthServer;

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

class CClientSession : public CNtlSession
{
public:
	CClientSession(bool bAliveCheck = false, bool bOpcodeCheck = false)
		:CNtlSession( SESSION_CLIENT )
	{
		SetControlFlag( CONTROL_FLAG_USE_SEND_QUEUE );
		if( bAliveCheck )
		{
			SetControlFlag( CONTROL_FLAG_CHECK_ALIVE );
		}
		if( bOpcodeCheck )
		{
			SetControlFlag( CONTROL_FLAG_CHECK_OPCODE );
		}

		SetPacketEncoder( &m_packetEncoder );
	}

	~CClientSession();

public:
	int								OnAccept();
	void							OnClose();
	int								OnDispatch(CNtlPacket * pPacket);
	int								ParseAuthPacket(CNtlPacket * pPacket);
	int								ParseFriendPacket(CNtlPacket * pPacket);
	int								ParseGroupePacket(CNtlPacket * pPacket);
	int								ParseGamePacket(CNtlPacket * pPacket);
	int								SendPacket(CNtlPacket * pPacket, int sleepTime = 0);
	void							Update(DWORD diff);
	bool							isInWorld();
	// Packet functions
	// LOGIN
		bool						SendCharLogInReq(CNtlPacket * pPacket, CAuthServer * app);
		void						SendLoginDcReq(CNtlPacket * pPacket);
		void						RefreshMyGroupHUD();
	// FRIEND
		void						SendFriendList();
		void						SendFriendToAddToGroupeRequest(CNtlPacket *pPacket, CAuthServer * app);
		void						SendFriendGroupe(CNtlPacket *pPacket, CAuthServer * app);
		void						SendFriendLogin(CAuthServer * app, bool online);
	// GAME
		void						SendMapList();
		void						SendGameEnterReq(CNtlPacket *pPacket, CAuthServer * app);
		void						SendGameEnterCompleteReq(CNtlPacket *pPacket, CAuthServer * app);
		void						SendCharacterMoveOnMap(CNtlPacket *pPacket, CAuthServer * app);
		void						SendBackToMenu(CNtlPacket *pPacket, CAuthServer * app);
		void						SendPopupMessage(const char* theString);
	// End Packet functions
private:
	CNtlPacketEncoder_RandKey		m_packetEncoder;
	SOCKET							sock;
// ATIDOTE THING
public:
	Client							*me;
	WSADATA							wsa;
	void							sendToAllPacket(CNtlPacket * pPacket, int accid);
};

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

class CAuthSessionFactory : public CNtlSessionFactory
{
public:

	CNtlSession * CreateSession(SESSIONTYPE sessionType)
	{
		CNtlSession * pSession = NULL;
		switch( sessionType )
		{
		case SESSION_CLIENT: 
			{
				pSession = new CClientSession;
			}
			break;

		default:
			break;
		}

		return pSession;
	}
};

//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//

class CAuthServer : public CNtlServerApp
{
public:
	const char*		GetConfigFileHost()
	{
		return m_config.Host.c_str();
	}
	const char*		GetConfigFileUser()
	{
		return m_config.User.c_str();
	}
	const char*		GetConfigFilePassword()
	{
		return m_config.Password.c_str();
	}
	const char*		GetConfigFileDatabase()
	{
		return m_config.Database.c_str();
	}
	const char*		GetConfigFileExternalIP()
	{
		std::cout << m_config.ExternalIP.c_str() << std::endl;
		return m_config.ExternalIP.c_str();
	}
	const bool		GetConfigFileSaveOnLogout()
	{
		return m_config.SaveOnLogout;
	}
	const int		GetConfigFileSaveInterval()
	{
		return m_config.saveInterval;
	}
	const int		GetConfigFilePlayerLimits()
	{
		return m_config.PlayerLimits;
	}
	int	OnInitApp()
	{
		m_nMaxSessionCount = MAX_NUMOF_SESSION;

		m_pSessionFactory =  new CAuthSessionFactory;
		if( NULL == m_pSessionFactory )
		{
			return NTL_ERR_SYS_MEMORY_ALLOC_FAIL;
		}

		return NTL_SUCCESS;
	}

	int	OnCreate()
	{
		int rc = NTL_SUCCESS;
		rc = m_clientAcceptor.Create(	m_config.strClientAcceptAddr.c_str(), m_config.wClientAcceptPort, SESSION_CLIENT, 
			m_config.PlayerLimits + MAX_NUMOF_SERVER, 5, 2, m_config.PlayerLimits + MAX_NUMOF_SERVER);
		if ( NTL_SUCCESS != rc )
		{
			return rc;
		}

		rc = m_network.Associate( &m_clientAcceptor, true );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}

		return NTL_SUCCESS;

	}

	void	OnDestroy()
	{
	}

	int	OnCommandArgument(int argc, _TCHAR* argv[])
	{
		return NTL_SUCCESS;
	}

	int	OnConfiguration(const char * lpszConfigFile)
	{
		CNtlIniFile file;

		int rc = file.Create( lpszConfigFile );
		if( NTL_SUCCESS != rc )
		{
			return rc;
		}
		if( !file.Read("IPAddress", "Address", m_config.ExternalIP) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("Auth Server", "Address", m_config.strClientAcceptAddr) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("Auth Server", "Port",  m_config.wClientAcceptPort) )
		{
			return NTL_ERR_SYS_CONFIG_FILE_READ_FAIL;
		}
		if( !file.Read("DATABASE", "Host",  m_config.Host) )
		{
			return NTL_ERR_DBC_HANDLE_ALREADY_ALLOCATED;
		}
		if( !file.Read("DATABASE", "User",  m_config.User) )
		{
			return NTL_ERR_SYS_MEMORY_ALLOC_FAIL;
		}
		if( !file.Read("DATABASE", "Password",  m_config.Password) )
		{
			return NTL_ERR_SYS_LOG_SYSTEM_INITIALIZE_FAIL;
		}
		if (!file.Read("DATABASE", "Db", m_config.Database))
		{
			return NTL_ERR_DBC_CONNECTION_CONNECT_FAIL;
		}
		if (!file.Read("PERFORMANCE", "PlayerLimit", m_config.PlayerLimits))
		{
			return NTL_ERR_DBC_CONNECTION_CONNECT_FAIL;
		}
		if (!file.Read("PERFORMANCE", "PlayerSaveInterval", m_config.saveInterval))
		{
			return NTL_ERR_DBC_CONNECTION_CONNECT_FAIL;
		}
		if (!file.Read("PERFORMANCE", "PlayerSaveStatsSaveOnlyOnLogout", m_config.SaveOnLogout))
		{
			return NTL_ERR_DBC_CONNECTION_CONNECT_FAIL;
		}
		return NTL_SUCCESS;
	}

	int	OnAppStart()
	{
		return NTL_SUCCESS;
	}
	void Run()
	{
		DWORD dwTickCur, dwTickOld = ::GetTickCount();
		DWORD saveTick, saveTickOld = ::GetTickCount();
		
		while (IsRunnable())
		{
			saveTick = dwTickCur = ::GetTickCount();
			if (dwTickCur - dwTickOld >= 1000)
			{
				Update(dwTickCur);
				dwTickOld = dwTickCur;
			}
			if (GetConfigFileSaveOnLogout() == 0)
			{
				if ((saveTick - saveTickOld) >= GetConfigFileSaveInterval())
				{
					saveTickOld = saveTick;
				}
			}
			Sleep(1);
		}
	}
	void									Update(DWORD diff);
	void									CheckOffline(DWORD diff);
public:
	bool									AddUser(const char * lpszUserID, CClientSession * pSession);
	void									RemoveUser(const char * lpszUserID);
	bool									FindUser(const char * lpszUserID);
	CClientSession							*GetPlayerByAccount(int accountID);
	CClientSession							*GetPlayerByName(const char* accName);
	void									SendToPlayerIfExist(const char * lpszUserID, CNtlPacket * pPacket);
	void									UpdateFriendList();
	DWORD									ThreadID;

	void									sendToAll(CNtlPacket * pPacket, int accid);


private:
	CNtlAcceptor							m_clientAcceptor;
	CNtlLog  								m_log;
	sSERVERCONFIG							m_config;
	CNtlMutex								server_mutex;
public:
	MySQLConnWrapper *						db;
	typedef std::map<CNtlString, CClientSession*> USERLIST;
	typedef USERLIST::value_type USERVAL;
	typedef USERLIST::iterator USERIT;
	USERLIST								m_userList;
};

#endif