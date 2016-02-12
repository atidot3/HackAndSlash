#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../../Server/GameServer.h"
#include "../../Session/Session.h"
#include "../Unit/Unit.h"

struct		NtlVector;
class		Client;
class		Unit;

class Player : public Unit
{
public:
	explicit Player()
	{
		disconnected = true;
		life = 100;
		level = 1;
		classe = 0;
	}
	~Player()	{}
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
	void		update(DWORD diff){}
	int			getGUID(){ return GUID; }
	void		setGUID(int id){ GUID = id; }
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