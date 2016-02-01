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
	for each (Map* map in m_mapList)
	{
		delete map;
	}
	m_mapList.clear();
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
	int diff = 0;
	while (sess->runnable == true)
	{
		update(diff);
		diff++;
		//std::cout << "looping update: " << diff <<  endl;
		std::this_thread::sleep_for(chrono::microseconds(10));
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
}
void Session::UpdateMap(int diff)
{
	for each (Map* map in m_mapList)
	{
		if (map != NULL)
		{
			map->Update(diff);
		}
	}
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