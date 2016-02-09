#ifndef _CHARACTERMANAGER
# define _CHARACTERMANAGER

#pragma once

#include "../Server/GameServer.h"

class CClientSession;
class CNtlPacket;
class CNtlMutex;

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();

	void Run();

	bool									AddUser(CClientSession* tmp);
	void									RemoveUser(CClientSession* tmp);
	bool									FindUser(const char * lpszUserID);
	CClientSession							*GetPlayerByAccount(int accountID);
	CClientSession							*GetPlayerByName(const char* accName);
	void									SendToPlayerIfExist(const char * lpszUserID, CNtlPacket * pPacket);
	void									UpdateFriendList();
	void									sendToAll(CNtlPacket * pPacket, int accid);

private:
	//Thread * pThread;
	//GameServer* pServer;
	DWORD									dwLastTick;
	CNtlMutex								server_mutex;
public:
	typedef std::list<CClientSession*> USERLIST;
	typedef USERLIST::value_type USERVAL;
	typedef USERLIST::iterator USERIT;
	USERLIST								m_userList;
};

#endif