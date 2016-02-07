#include "Session.h"

Session::Session()
{
	runnable = true;
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	hProcessThread = CreateThread(NULL, 0, &Session::StaticThreadStart, this, 0, &app->ThreadID);
	if (hProcessThread == NULL)
	{
	}
	app->ThreadID++;
}
Session::~Session()
{
	runnable = false;
	std::cout << "destructor" << endl;
	if (m_mapList.size() > 0 && m_mapList.size() < 100)
	{
		for each (Map* map in m_mapList)
		{
			delete map;
		}
		m_mapList.clear();
	}
	std::cout << "end" << endl;
}
bool Session::AddPlayerToSession(Client* client)
{
	if (isPlayerInSession(client) == true)
		return false;
	lock();
	if (m_memberLists.size() < MAX_PLAYER_PER_MAP)
	{
		m_memberLists.push_back(client);
		unlock();
		return true;
	}
	unlock();
	return false;
}
bool Session::isPlayerInSession(Client* _cl)
{
	lock();
	for each (Client* cl in m_memberLists)
	{
		if (cl->getAccountID() == _cl->getAccountID())
		{
			unlock();
			return true;
		}
	}
	return false;
	unlock();
}
void Session::RemovePlayerFromSession()
{
	lock();
	m_memberLists.clear();
	unlock();
}
void Session::RemovePlayer(Client* _cl)
{
	lock();
	bool founded = false;
	for each (Client* cl in m_memberLists)
	{
		if (cl->getAccountID() == _cl->getAccountID())
		{
			founded = true;
			break;
		}
	}
	if (founded == true)
	{
		RemovePlayerFromMap(_cl->getPlayer(), true);
		m_memberLists.remove(_cl);
	}
	unlock();
}
void Session::CreateMap(int mapID)
{
	lock();
	Map* map = new Map(mapID);
	map->setDifficulty(m_dungeonDifficulty);
	m_mapList.push_back(map);
	unlock();
	//map.start(); //start map thread
}
void Session::RemoveMap(int mapID)
{
	lock();
	std::list<Map*>::iterator	it;
	it = m_mapList.begin();
	Map* maps = NULL;
	while (it != m_mapList.end())
	{
		if ((*it)->getMapID() == mapID)
		{
			maps = (*it);
			break;
		}
		++it;
	}
	if (maps != NULL)
	{
		m_mapList.remove(maps);
	}
	unlock();
}
void Session::changeMap(int from, int to, Player* plr)
{
	bool mapToFounded = false;
	for each (Map* map in m_mapList)
	{
		if (map->getMapID() == from)
		{
			map->RemovePlayerFromMap(plr, true);
		}
		if (map->getMapID() == to)
		{
			map->AddPlayerToMap(plr);
			mapToFounded = true;
		}
	}
	if (mapToFounded == false)
	{
		CreateMap(to);
		//map.start();
	}
}
void Session::AddPlayerToMap(int mapID, Player* plr)
{
	lock();
	Map *map = isMapExist(mapID);
	if (map == NULL)
	{
		std::cout << "create map" << endl;
		CreateMap(mapID);
	}
	for each (Map* map in m_mapList)
	{
		if (map->getMapID() == mapID)
		{
			map->AddPlayerToMap(plr);
			// create packet to update player map etc
		}
	}
	unlock();
}
void Session::RemovePlayerFromMap(Player *plr, bool del)
{
	lock();
	for each (Map* map in m_mapList)
	{
		if (map != NULL)
		{
			map->RemovePlayerFromMap(plr, del);
		}
	}
	unlock();
}
void Session::SendMovementPlayer(Player* plr, int mapID, CNtlPacket *packet)
{
	Map *map = isMapExist(mapID);
	if (map != NULL)
	{
		map->SendToOther(packet, plr);
	}
}
void Session::UpdateDifficulty(Difficulty dif)
{
	m_dungeonDifficulty = dif;
}
void Session::PreDestruct()
{
	runnable = false;
	Sleep(15);
	CloseHandle(hProcessThread);
}
DWORD Session::PreUpdate(Session *sess)
{
	while (sess->runnable == true)
	{
		update(::GetTickCount());
		//std::cout << "looping update: " << diff <<  endl;
		Sleep(1);
	}
	return 0;
}
void Session::update(int diff)
{
	if ((isPlayerPlaying()) == false)
	{
		RemovePlayerFromSession();
		runnable = false;
	}
	UpdateMap(diff);
	UpdatePlayer(diff);
}
void Session::UpdatePlayer(DWORD diff)
{
	lock();
	for each (Client* plr in m_memberLists)
	{
		if (plr)
		{
			if (plr->getStatut() == ClientStatut::GAME)
			{
				if (plr->getPlayer() != NULL)
				{
					plr->getPlayer()->update(diff);
				}
			}
		}
	}
	unlock();
}
void Session::UpdateMap(DWORD diff)
{
	lock();
	for each (Map* map in m_mapList)
	{
		if (map != NULL)
		{
			map->Update(diff);
		}
	}
	unlock();
}
Map *Session::isMapExist(int mapID)
{
	lock();
	for each (Map* map in m_mapList)
	{
		if (map->getMapID() == mapID)
		{
			unlock();
			return map;
		}
	}
	unlock();
	return NULL;
}
bool Session::isPlayerPlaying()
{
	lock();
	for each (Client* cl in m_memberLists)
	{
		if (cl->getStatut() == ClientStatut::GAME)
		{
			unlock();
			return true;
		}
	}
	unlock();
	return false;
}
void Session::ClearMaps()
{
	lock();
	for each (Map* map in m_mapList)
	{
		delete map;
	}
	m_mapList.clear();
	unlock();
}
void Session::lock()
{
	session_mutex.Lock();
}
void Session::unlock()
{
	session_mutex.Unlock();
}