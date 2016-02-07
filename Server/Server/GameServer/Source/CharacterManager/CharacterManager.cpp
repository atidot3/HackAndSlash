#include "CharacterManager.h"

CharacterManager::CharacterManager()
{

}
CharacterManager::~CharacterManager()
{
}
void 						CharacterManager::Run()
{
	server_mutex.Lock();
	DWORD currentTick = ::GetTickCount();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		it->second->Update(currentTick);
	}
	server_mutex.Lock();
}

void						CharacterManager::sendToAll(CNtlPacket * pPacket, int accid)
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = it->second;
		if (plr != NULL)
		{
			//if (plr->me->getAccountID() != accid)
				plr->SendPacket(pPacket);
		}
	}
	server_mutex.Unlock();
}
void						CharacterManager::SendToPlayerIfExist(const char * lpszUserID, CNtlPacket * pPacket)
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
CClientSession				*CharacterManager::GetPlayerByAccount(int accountID)
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
bool						CharacterManager::AddUser(const char * lpszUserID, CClientSession * pSession)
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
void						CharacterManager::RemoveUser(const char * lpszUserID)
{
	server_mutex.Lock();
	m_userList.erase(CNtlString(lpszUserID));
	server_mutex.Unlock();
}
bool						CharacterManager::FindUser(const char * lpszUserID)
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
CClientSession				*CharacterManager::GetPlayerByName(const char* accName)
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
void						CharacterManager::UpdateFriendList()
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