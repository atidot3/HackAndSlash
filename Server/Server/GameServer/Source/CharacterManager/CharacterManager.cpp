#include "CharacterManager.h"
#include <list>

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
		(*it)->Update(currentTick);
	}
	server_mutex.Lock();
}

void						CharacterManager::sendToAll(CNtlPacket * pPacket, int accid)
{
	server_mutex.Lock();
	USERIT it;
	for (it = m_userList.begin(); it != m_userList.end(); it++)
	{
		CClientSession *plr = (*it);
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
		CClientSession *plr = (*it);
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
		CClientSession *plr = (*it);
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
bool						CharacterManager::AddUser(CClientSession * pSession)
{
	server_mutex.Lock();
	m_userList.push_back(pSession);
	server_mutex.Unlock();
	/*if (false == m_userList.insert(USERVAL(CNtlString(lpszUserID), pSession)).second)
	{
		server_mutex.Unlock();
		return false;
	}
	server_mutex.Unlock();*/
	return true;
}
void						CharacterManager::RemoveUser(CClientSession* tmp)
{

	server_mutex.Lock();
	for (USERIT it = m_userList.begin(); it != m_userList.end(); ++it)
	{
		if ((*it)->me->getAccountID() == tmp->me->getAccountID())
		{
			m_userList.erase(it);
			std::cout << "User :" << tmp->me->getAccountName() << " Removed, list size: " << m_userList.size() << std::endl;
			break;
		}
	}
	server_mutex.Unlock();
}
bool						CharacterManager::FindUser(const char * lpszUserID)
{
	server_mutex.Lock();
	for (USERIT it = m_userList.begin(); it != m_userList.end(); ++it)
	{
		if (it == m_userList.end())
		{
			server_mutex.Unlock();
			return false;
		}
		if ((*it)->me->getAccountName().c_str() == lpszUserID)
		{
			server_mutex.Unlock();
			return true;
			break;
		}
	}
	server_mutex.Unlock();
	return false;
}
CClientSession				*CharacterManager::GetPlayerByName(const char* accName)
{
	server_mutex.Lock();
	//USERIT it = m_userList.begin();
	USERIT it = m_userList.begin();
	while (it != m_userList.end())
	{
		CClientSession *plr = (*it);
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
		CClientSession *plr = (*it);
		if (plr != NULL)
		{
			plr->SendFriendList();
		}
	}
	server_mutex.Unlock();
}