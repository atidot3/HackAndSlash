#ifndef _OBJECT_H
#define _OBJECT_H

#include "../ObjectGUID.h"

class Creature;
class GameObject;
class Player;
class Unit;

class Object
{
public:
	virtual ~Object();

	bool IsInWorld() const { return m_inWorld; }

	virtual void AddToWorld();
	virtual void RemoveFromWorld();

	TypeID GetTypeId() const { return m_objectTypeId; }
	bool isType(TypeID type) const { return (type & m_objectTypeId) != 0; }

	void SendUpdateToPlayer(Player* player);

	virtual void DestroyForPlayer(Player* target) const;
	virtual void Update(DWORD /*time_diff*/) { }

	void SetFlag(uint16 index, uint32 newFlag);
	void RemoveFlag(uint16 index, uint32 oldFlag);
	bool HasFlag(uint16 index, uint32 flag) const;

	void ClearUpdateMask(bool remove);

	virtual bool hasQuest(uint32 ) const { return false; }

	Player* ToPlayer() { if (GetTypeId() == TYPEID_PLAYER) return reinterpret_cast<Player*>(this); else return NULL; }
	Player const* ToPlayer() const { if (GetTypeId() == TYPEID_PLAYER) return reinterpret_cast<Player const*>(this); else return NULL; }

	Creature* ToCreature() { if (GetTypeId() == TYPEID_UNIT) return reinterpret_cast<Creature*>(this); else return NULL; }
	Creature const* ToCreature() const { if (GetTypeId() == TYPEID_UNIT) return reinterpret_cast<Creature const*>(this); else return NULL; }

	Unit* ToUnit() { if (isType(TYPEID_UNIT)) return reinterpret_cast<Unit*>(this); else return NULL; }
	Unit const* ToUnit() const { if (isType(TYPEID_UNIT)) return reinterpret_cast<Unit const*>(this); else return NULL; }

	GameObject* ToGameObject() { if (GetTypeId() == TYPEID_GAMEOBJECT) return reinterpret_cast<GameObject*>(this); else return NULL; }
	GameObject const* ToGameObject() const { if (GetTypeId() == TYPEID_GAMEOBJECT) return reinterpret_cast<GameObject const*>(this); else return NULL; }

protected:
	Object();
	TypeID m_objectTypeId;
private:
	bool m_inWorld;
};

#endif