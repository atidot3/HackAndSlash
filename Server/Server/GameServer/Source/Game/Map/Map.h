#ifndef _MAP_H_
# define _MAP_H_

#include "../../Packets/AllPackets.h"
#include "../Groupe/Groupe.h"
#include "../Session/Session.h"
#include "../../Server/GameServer.h"


#define MAX_PLAYER_PER_MAP	5

enum Difficulty;
class Player;

class Map
{
public:
	Map(int id);
	~Map();
	bool			AddPlayerToMap(Player* player, bool initPlayer = true);
	void			RemovePlayerFromMap(Player*, bool);
	void			Update(DWORD);
	bool			HavePlayers();
	void			SendToPlayers(CNtlPacket *pPacket);
	void			UpdateDifficulty(Difficulty dif);
	void			setMapID(int id);
	int				getMapID(){ return mapID; }
	void			lock();
	void			unlock();
	void			setDifficulty(Difficulty diff){ m_dungeonDifficulty = diff; }
	int				getGUID();
	// SEND
	void			SendToAll(CNtlPacket *pPacket);
	void			SendData(CNtlPacket *pPacket, Player* plr);
	void			SendToOther(CNtlPacket *pPacket, Player *plr);
	// PACKET
	void			createAddPlayerToMapPacket(Player* plr);
	void			createSpawnMembersPacket(Player *plr);
	void			createDeleteMembersPacket(Player *plr);
private:
	int								mapID;
	typedef std::list<Player*>		MemberList;
	MemberList						m_memberLists;
	CNtlMutex						map_mutex;
	Difficulty						m_dungeonDifficulty;
	int								lastGUID;
};


#endif