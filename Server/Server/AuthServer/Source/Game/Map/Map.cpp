#include "Map.h"

Map::~Map()
{
	std::cout << "Map destructor called" << endl;
	m_memberLists.clear();
}
Map::Map(int id)
{
	mapID = id;
}
bool Map::AddPlayerToMap(Player* player, bool initPlayer /*= true*/)
{
	lock();
	if (m_memberLists.size() < MAX_PLAYER_PER_MAP)
	{
		m_memberLists.push_back(player);
		if (m_memberLists.size() > 1)
		{
			createSpawnMembersPacket(player);
			createAddPlayerToMapPacket(player);
		}
		unlock();
		return true;
	}
	unlock();
	return false;
}
void  Map::createAddPlayerToMapPacket(Player* plr)
{
	CNtlPacket packet(sizeof(sGU_PARTY_MEMBER_SPAWN));
	sGU_PARTY_MEMBER_SPAWN * res = (sGU_PARTY_MEMBER_SPAWN *)packet.GetPacketData();

	res->group[0].charId = plr->getClient()->getAccountID();
	res->group[0].level = plr->getLevel();
	res->group[0].location = plr->getLocation();
	strcpy(res->group[0].name, plr->getClient()->getAccountName().c_str());
	res->count = 1;
	res->wOpCode = GU_PARTY_MEMBER_SPAWN;
	packet.SetPacketLen(sizeof(sGU_PARTY_MEMBER_SPAWN));
	SendToOther(&packet, plr);
}
void Map::createSpawnMembersPacket(Player *plr)
{
	CNtlPacket packet(sizeof(sGU_PARTY_MEMBER_SPAWN));
	sGU_PARTY_MEMBER_SPAWN * res = (sGU_PARTY_MEMBER_SPAWN *)packet.GetPacketData();

	int i = 0;
	for each (Player *pl in m_memberLists)
	{
		if (pl->getClient()->getAccountID() != plr->getClient()->getAccountID())
		{
			res->group[i].charId = pl->getClient()->getAccountID();
			res->group[i].level = pl->getLevel();
			res->group[i].location = pl->getLocation();
			strcpy(res->group[i].name, pl->getClient()->getAccountName().c_str());
			i++;
			res->count++;
		}
	}
	if (res->count > 0)
	{
		res->wOpCode = GU_PARTY_MEMBER_SPAWN;
		packet.SetPacketLen(sizeof(sGU_PARTY_MEMBER_SPAWN));
		SendData(&packet, plr);
	}
}
void Map::createDeleteMembersPacket(Player *plr)
{
	CNtlPacket packet(sizeof(sGU_PARTY_MEMBER_LOGOUT));
	sGU_PARTY_MEMBER_LOGOUT * res = (sGU_PARTY_MEMBER_LOGOUT *)packet.GetPacketData();
	
	res->charID = plr->getClient()->getAccountID();
	res->wOpCode = GU_PARTY_MEMBER_LOGOUT;

	packet.SetPacketLen(sizeof(sGU_PARTY_MEMBER_LOGOUT));
	SendToOther(&packet, plr);
}
void Map::RemovePlayerFromMap(Player* player, bool remove)
{
	if (player == NULL)
		return;
	lock();
	std::list<Player*>::iterator	it;
	it = m_memberLists.begin();
	Player* plr = NULL;
	while (it != m_memberLists.end())
	{
		if ((*it)->getClient()->getAccountID() == player->getClient()->getAccountID())
		{
			plr = (*it);
			break;
		}
		++it;
	}
	if (plr != NULL)
	{
		m_memberLists.remove(plr);
	}
	unlock();
	if (plr != NULL)
	{
		createDeleteMembersPacket(plr);
	}
}
void Map::Update(DWORD t_diff)
{
	
}
bool Map::HavePlayers()
{
	lock();
	if (m_memberLists.size() > 0)
	{
		unlock();
		return true;
	}
	unlock();
	return false;
}
void Map::UpdateDifficulty(Difficulty dif)
{

}
void Map::SendData(CNtlPacket *pPacket, Player* plr)
{
	plr->getClient()->getSession()->SendPacket(pPacket);
}
void Map::SendToAll(CNtlPacket *pPacket)
{
	lock();
	for each (Player *pl in m_memberLists)
	{
		pl->getClient()->getSession()->SendPacket(pPacket);
	}
	unlock();
}
void Map::SendToOther(CNtlPacket *pPacket, Player *plr)
{
	lock();
	for each (Player *pl in m_memberLists)
	{
		if (pl->getClient()->getAccountID() != plr->getClient()->getAccountID())
		{
			if (pl->getClient()->getSession()->isInWorld() == true)
				pl->getClient()->getSession()->SendPacket(pPacket);
		}
	}
	unlock();
}
void Map::lock()
{
	map_mutex.Lock();
}
void Map::unlock()
{
	map_mutex.Unlock();
}