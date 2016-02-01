//-----------------------------------------------------------------------------------
//		Auth Server by Daneos @ Ragezone 
//-----------------------------------------------------------------------------------

#include "stdafx.h"
#include "AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

using namespace std;

void CAuthServer::Update(DWORD diff)
{
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		it->second->Update(diff);
	}
}
//-----------------------------------------------------------------------------------
CClientSession::~CClientSession()
{
	//NTL_PRINT(PRINT_APP, "CClientSession Destructor Called");
}
int							CClientSession::OnAccept()
{
	//NTL_PRINT( PRINT_APP, "%s", __FUNCTION__ );
	return NTL_SUCCESS;
}
void						CClientSession::OnClose()
{
	//NTL_PRINT( PRINT_APP, "%s", __FUNCTION__ );
	CAuthServer * app = (CAuthServer*) NtlSfxGetApp();
}
int							CClientSession::SendPacket(CNtlPacket * pPacket, int sleepTime)
{
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	int header = pHeader->wOpCode;
	int rc = g_pApp->Send(this->GetHandle(), pPacket);
	//std::cout << "Packet sended " << i++ << " size packet: " << pPacket->GetUsedSize() << " Opcode: " << header << endl;
	return rc;
}
void						CClientSession::Update(DWORD diff)
{
	if (!isInWorld())
		return;
	//std::cout << "client: " << me->getAccountID() << " with name: " << me->getAccountName() << " Updating" << std::endl;
	//std::cout << diff << std::endl;
}
bool						CClientSession::isInWorld()
{
	if (me != NULL)
	{
		if (me->getPlayer() != NULL)
		{
			if (ClientStatut::GAME == me->getStatut())
			{
				return true;
			}
		}
	}
	return false;
}
void						CClientSession::sendToAllPacket(CNtlPacket * pPacket, int accid)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();

	app->sendToAll(pPacket, accid);
}
void						CAuthServer::sendToAll(CNtlPacket * pPacket, int accid)
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			if (plr->me->getAccountID() != accid)
				plr->SendPacket(pPacket);
		}
	}
	server_mutex.Unlock();
}
void						CAuthServer::SendToPlayerIfExist(const char * lpszUserID, CNtlPacket * pPacket)
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			if (strcmp(plr->me->getAccountName().c_str(), lpszUserID) == 0)
			{
				plr->SendPacket(pPacket);
				break;
			}
		}
	}
	server_mutex.Unlock();
}
CClientSession				*CAuthServer::GetPlayerByAccount(int accountID)
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			if (plr->me->getAccountID() == accountID)
			{
				server_mutex.Unlock();
				return plr;
			}
		}
	}
	server_mutex.Unlock();
	return NULL;
}
bool						CAuthServer::AddUser(const char * lpszUserID, CClientSession * pSession)
{
	server_mutex.Lock();
	if (false == m_userList.insert(USERVAL(CNtlString(lpszUserID), pSession)).second)
	{
		server_mutex.Unlock();
		return false;
	}
	server_mutex.Unlock();
	return true;
}
void						CAuthServer::RemoveUser(const char * lpszUserID)
{
	server_mutex.Lock();
	m_userList.erase(CNtlString(lpszUserID));
	server_mutex.Unlock();
}
bool						CAuthServer::FindUser(const char * lpszUserID)
{
	server_mutex.Lock();
	USERIT it = m_userList.find(CNtlString(lpszUserID));
	if (it == m_userList.end())
	{
		server_mutex.Unlock();
		return false;
	}
	server_mutex.Unlock();
	return true;
}
CClientSession				*CAuthServer::GetPlayerByName(const char* accName)
{
	server_mutex.Lock();
	USERIT it = m_userList.begin();
	while (it != m_userList.end())
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			if (strcmp(plr->me->getAccountName().c_str(), accName) == 0)
			{
				server_mutex.Unlock();
				return plr;
			}
		}
		++it;
	}
	server_mutex.Unlock();
	return NULL;
}
void						CAuthServer::UpdateFriendList()
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			plr->SendFriendList();
		}
	}
	server_mutex.Unlock();
}
int							CClientSession::OnDispatch(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*) NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	/*if (pHeader->wOpCode == 1)
	{
		if (me != NULL)
		{
			me->lastPing = ::GetTickCount();
		}
	}*/
	if (pHeader->wOpCode >= UA_OPCODE_BEGIN && pHeader->wOpCode <= UA_OPCODE_END)
	{
		ParseAuthPacket(pPacket);
	}
	else if (pHeader->wOpCode >= UF_OPCODE_BEGIN && pHeader->wOpCode <= UF_OPCODE_END)
	{
		ParseFriendPacket(pPacket);
	}
	else if (pHeader->wOpCode >= UG_OPCODE_BEGIN && pHeader->wOpCode <= UG_OPCODE_END || pHeader->wOpCode == GU_PARTY_MEMBER_MOVE)
	{
		ParseGamePacket(pPacket);
	}
	return NTL_SUCCESS;
}

//-----------------------------------------------------------------------------------
//		AuthServerMain
//-----------------------------------------------------------------------------------
int AuthServerMain(int argc, _TCHAR* argv[])
{
	CAuthServer app;
	CNtlFileStream traceFileStream;

	// LOG FILE
	int rc = traceFileStream.Create("GameLog");
	if (NTL_SUCCESS != rc)
	{
		printf("log file CreateFile error %d(%s)", rc, NtlGetErrorMessage(rc));
		return rc;
	}

	// CHECK INI FILE AND START PROGRAM
	NtlSetPrintStream(traceFileStream.GetFilePtr());
	NtlSetPrintFlag(PRINT_APP | PRINT_SYSTEM);

	rc = app.Create(argc, argv, ".\\Server.ini");
	if (NTL_SUCCESS != rc)
	{
		NTL_PRINT(PRINT_APP, "Server Application Create Fail %d(%s)", rc, NtlGetErrorMessage(rc));
		return rc;
	}

	// CONNECT TO MYSQL
	app.db = new MySQLConnWrapper;
	app.db->setConfig(app.GetConfigFileHost(), app.GetConfigFileUser(), app.GetConfigFilePassword(), app.GetConfigFileDatabase());
	try
	{
		app.db->connect();
		NTL_PRINT(PRINT_APP, "Connected to database server.");
	}
	catch (exception e)
	{
		NTL_PRINT(PRINT_APP, "couldn't connect to database server ErrID:%s", e.what());
	}
	try
	{
		app.db->switchDb(app.GetConfigFileDatabase());
	}
	catch (exception e)
	{
		NTL_PRINT(PRINT_APP, "Couldn't switch database to %s Error:%s", app.GetConfigFileDatabase(), e.what());
	}
	app.Start();
	Sleep(500);
	/*std::cout << "\n\n" << std::endl;
	std::cout << "\t  ____                              ____        _ _ " << std::endl;
	std::cout << "\t |  _ \\ _ __ __ _  __ _  ___  _ __ | __ )  __ _| | |" << std::endl;
	std::cout << "\t | | | | '__/ _` |/ _` |/ _ \\| '_ \\|  _ \\ / _` | | |" << std::endl;
	std::cout << "\t | |_| | | | (_| | (_| | (_) | | | | |_) | (_| | | |" << std::endl;
	std::cout << "\t |____/|_|  \\__,_|\\__, |\\___/|_| |_|____/ \\__,_|_|_|" << std::endl;
	std::cout << "\t                  |___/                             " << std::endl;*/
	std::cout << "\t______           AKCore :O 2015					______\n\n" << std::endl;
	app.WaitForTerminate();
	return 0;
}
