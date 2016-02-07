#ifndef _SESSION_H_
# define _SESSION_H_

#include "../../Packets/AllPackets.h"
#include "../Groupe/Groupe.h"
#include "../../Server/GameServer.h"
#include "../Map/Map.h"
#include <thread>
#include <chrono>
#include <mutex>

class Player;
class Map;
enum Difficulty;
class Client;

class Session
{
public:
	Session();
	~Session();
	void							CreateMap(int mapID);
	void							RemoveMap(int mapID);
	void							UpdateDifficulty(Difficulty dif);
	void							changeMap(int from, int to, Player* plr);
	void							update(int diff);
	DWORD							PreUpdate(Session *sess);
	void							PreDestruct();
	void							AddPlayerToMap(int mapID, Player* plr);
	void							RemovePlayerFromMap(Player *plr, bool del);
	void							SendMovementPlayer(Player* plr, int mapID, CNtlPacket *packet);
	bool							isPlayerPlaying();
	void							UpdateMap(DWORD diff);
	void							UpdatePlayer(DWORD diff);
	void							ClearMaps();
	bool							AddPlayerToSession(Client* client);
	void							RemovePlayerFromSession();
	void							RemovePlayer(Client* cl);
	bool							isPlayerInSession(Client* cl);
	void							lock();
	void							unlock();
	static DWORD WINAPI				StaticThreadStart(void* Param)
	{
		Session* This = (Session*)Param;
		return This->PreUpdate(This);
	}
	Map								*isMapExist(int mapID);
protected:
	Difficulty						m_dungeonDifficulty;
	std::list<Map*>					m_mapList;
	typedef std::list<Client*>		ClientList;
	ClientList						m_memberLists;
	HANDLE							hProcessThread;
	bool							runnable;
	CNtlMutex						session_mutex;
};

#endif