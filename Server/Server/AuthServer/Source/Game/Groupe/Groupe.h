#ifndef _GROUPE_H_
# define _GROUPE_H_

#include "../../Packets/AllPackets.h"
#include "../../Server/AuthServer.h"
#include "../../Packets/Game/PacketUG.h"
#include "../Session/Session.h"
#pragma once

#define MAX_GROUP_SIZE      5

enum Difficulty
{
	DIFFICULTY_NONE = 0,
	DIFFICULTY_NORMAL = 1,
	DIFFICULTY_HEROIC = 2,
	DIFFICULTY_10_N = 3,
	DIFFICULTY_25_N = 4,
	DIFFICULTY_10_HC = 5,
	DIFFICULTY_25_HC = 6,
	DIFFICULTY_LFR = 7,
	DIFFICULTY_CHALLENGE = 8,
	DIFFICULTY_40 = 9,
	DIFFICULTY_HC_SCENARIO = 11,
	DIFFICULTY_N_SCENARIO = 12,
	DIFFICULTY_NORMAL_RAID = 14,
	DIFFICULTY_HEROIC_RAID = 15,
	DIFFICULTY_MYTHIC_RAID = 16,
	DIFFICULTY_LFR_NEW = 17,
	DIFFICULTY_EVENT_RAID = 18,
	DIFFICULTY_EVENT_DUNGEON = 19,
	DIFFICULTY_EVENT_SCENARIO = 20,
	DIFFICULTY_MYTHIC = 23,
	DIFFICULTY_TIMEWALKER = 24,

	MAX_DIFFICULTY
};

class Client;
class Group;
class Session;

class Player
{
public:
	Player(){ disconnected = true; }
	~Player(){}
	void		setDisconnected(bool di){ disconnected = di; }
	bool		getDisconnedted(){ return disconnected; }
	void		setGroup(Group *grp){ group = grp; }
	Group		*getGroup(){ return group; }
	void		setLife(int amnt){ life = amnt; }
	int			getLife(){ return life; }
	void		setLevel(int lvl){ level = lvl; }
	int			getLevel(){ return level; }
	void		setClient(Client *me){ cl = me; }
	Client		*getClient(){ return cl; }
	void		setLocation(NtlVector _location){ location = _location; }
	NtlVector	getLocation(){ return location; }
private:
	bool		disconnected;
	Group		*group;
	int			level;
	int			life;
	Client		*cl;
	NtlVector	location;
};

class Group
{
public:
	struct MemberSlot
	{
		int			guid;
		std::string name;
		int			_class;
		int			group;
		int			flags;
		int			roles;
		bool        readyChecked;
		bool		disconnected;
		Player		*me;
	};
	typedef std::list<MemberSlot> MemberSlotList;
	typedef MemberSlotList::const_iterator member_citerator;
protected:
	typedef MemberSlotList::iterator member_witerator;
public:
	Group();
	~Group();
	// group manipulation methods
	bool				Create(Player* leader);
	bool				AddMember(Player* player);
	bool				RemoveMember(Player* player);
	void				ChangeLeader(Player* player);
	void				Disband(bool hideDestroy = false);
	int					GetMembersCount() { return int(m_memberSlots.size()); }
	void				RefreshAllGroup();
	// Update
	void				Update(int diff);
	// properties accessories
	bool				IsFull();
	void				SetDungeonDifficultyID(Difficulty difficulty);
	Difficulty			GetDifficultyID();
	// SEND
	void				SendUpdate(CNtlPacket *pPacket);
	void				SendAll(CNtlPacket *pPacket);
	// SESSION
	void				setSession(Session *s){ sess = s; }
	Session				*getSession(){ return sess; }
protected:
	Difficulty          m_dungeonDifficulty;
	MemberSlotList      m_memberSlots;
	Session				*sess;
};


#endif