#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../../Server/GameServer.h"
#include "../../Session/Session.h"
#include "../Unit/Unit.h"
#include "../ObjectGUID.h"

struct		NtlVector;
class		Client;
class		Unit;
class		Object;

class Player : public Unit
{
public:
	explicit Player();
	~Player()	{}


	void		AddToWorld() override;
	void		RemoveFromWorld() override;
	int			getClass(){ return classe; }
	void		setClass(int _class){ classe = _class; }
	void		setDisconnected(bool di){ disconnected = di; }
	bool		getDisconnedted(){ return disconnected; }
	void		setLife(int amnt){ life = amnt; }
	int			getLife(){ return life; }
	void		setLevel(int lvl){ level = lvl; }
	int			getLevel(){ return level; }
	void		setClient(Client *me){ cl = me; }
	Client		*getClient(){ return cl; }
	void		setLocation(NtlVector _location){ location = _location; }
	NtlVector	getLocation(){ return location; }
	void		Update(DWORD time) override;
	int			getGUID(){ return GUID; }
	void		setGUID(int id){ GUID = id; }
	/*********************************************************/
	/***                    QUEST SYSTEM                   ***/
	/*********************************************************/

	/*********************************************************/
	/***                   LOAD SYSTEM                     ***/
	/*********************************************************/

	/*********************************************************/
	/***                   SAVE SYSTEM                     ***/
	/*********************************************************/
private:
	bool		disconnected;
	int			level;
	int			life;
	Client		*cl;
	NtlVector	location;
	int			classe;
	int			GUID;
};

#endif