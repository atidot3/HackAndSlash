#ifndef _OBJECT_H
#define _OBJECT_H

#include <set>
#include <string>
#include <sstream>
#include <stdint.h>

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

class Creature;
class GameObject;
class Player;
class Unit;
class WorldObject;

class Object
{
public:
	/*virtual ~Object();

	bool IsInWorld() const { return m_inWorld; }

	virtual void AddToWorld();
	virtual void RemoveFromWorld();

	ObjectGuid const& GetGUID() const { return GetGuidValue(OBJECT_FIELD_GUID); }
	PackedGuid const& GetPackGUID() const { return m_PackGUID; }
	uint32 GetEntry() const { return GetUInt32Value(OBJECT_FIELD_ENTRY); }
	void SetEntry(uint32 entry) { SetUInt32Value(OBJECT_FIELD_ENTRY, entry); }

	TypeID GetTypeId() const { return m_objectTypeId; }
	bool isType(uint16 mask) const { return (mask & m_objectType) != 0; }

	void SendUpdateToPlayer(Player* player);

	virtual void DestroyForPlayer(Player* target) const;

	int32 GetInt32Value(uint16 index) const;
	uint32 GetUInt32Value(uint16 index) const;
	uint64 GetUInt64Value(uint16 index) const;
	float GetFloatValue(uint16 index) const;
	uint8 GetByteValue(uint16 index, uint8 offset) const;
	uint16 GetUInt16Value(uint16 index, uint8 offset) const;
	ObjectGuid const& GetGuidValue(uint16 index) const;

	void SetInt32Value(uint16 index, int32 value);
	void SetUInt32Value(uint16 index, uint32 value);
	void UpdateUInt32Value(uint16 index, uint32 value);
	void SetUInt64Value(uint16 index, uint64 value);
	void SetFloatValue(uint16 index, float value);
	void SetByteValue(uint16 index, uint8 offset, uint8 value);
	void SetUInt16Value(uint16 index, uint8 offset, uint16 value);
	void SetGuidValue(uint16 index, ObjectGuid const& value);
	void SetStatFloatValue(uint16 index, float value);
	void SetStatInt32Value(uint16 index, int32 value);

	bool AddGuidValue(uint16 index, ObjectGuid const& value);
	bool RemoveGuidValue(uint16 index, ObjectGuid const& value);

	void ApplyModUInt32Value(uint16 index, int32 val, bool apply);
	void ApplyModInt32Value(uint16 index, int32 val, bool apply);
	void ApplyModUInt16Value(uint16 index, uint8 offset, int16 val, bool apply);
	void ApplyModPositiveFloatValue(uint16 index, float val, bool apply);
	void ApplyModSignedFloatValue(uint16 index, float val, bool apply);
	void ApplyPercentModFloatValue(uint16 index, float val, bool apply);

	void SetFlag(uint16 index, uint32 newFlag);
	void RemoveFlag(uint16 index, uint32 oldFlag);
	void ToggleFlag(uint16 index, uint32 flag);
	bool HasFlag(uint16 index, uint32 flag) const;
	void ApplyModFlag(uint16 index, uint32 flag, bool apply);

	void SetByteFlag(uint16 index, uint8 offset, uint8 newFlag);
	void RemoveByteFlag(uint16 index, uint8 offset, uint8 newFlag);
	void ToggleByteFlag(uint16 index, uint8 offset, uint8 flag);
	bool HasByteFlag(uint16 index, uint8 offset, uint8 flag) const;

	void SetFlag64(uint16 index, uint64 newFlag);
	void RemoveFlag64(uint16 index, uint64 oldFlag);
	void ToggleFlag64(uint16 index, uint64 flag);
	bool HasFlag64(uint16 index, uint64 flag) const;
	void ApplyModFlag64(uint16 index, uint64 flag, bool apply);

	std::vector<uint32> const& GetDynamicValues(uint16 index) const;
	void AddDynamicValue(uint16 index, uint32 value);
	void RemoveDynamicValue(uint16 index, uint32 value);
	void ClearDynamicValue(uint16 index);
	void SetDynamicValue(uint16 index, uint8 offset, uint32 value);

	void ClearUpdateMask(bool remove);

	uint16 GetValuesCount() const { return m_valuesCount; }

	virtual bool hasQuest(uint32 ) const { return false; }
	virtual bool hasInvolvedQuest(uint32 ) const { return false; }
	virtual void BuildUpdate(UpdateDataMapType&) { }
	void BuildFieldsUpdate(Player*, UpdateDataMapType &) const;

	void SetFieldNotifyFlag(uint16 flag) { _fieldNotifyFlags |= flag; }
	void RemoveFieldNotifyFlag(uint16 flag) { _fieldNotifyFlags &= uint16(~flag); }

	// FG: some hacky helpers
	void ForceValuesUpdateAtIndex(uint32);

	Player* ToPlayer() { if (GetTypeId() == TYPEID_PLAYER) return reinterpret_cast<Player*>(this); else return NULL; }
	Player const* ToPlayer() const { if (GetTypeId() == TYPEID_PLAYER) return reinterpret_cast<Player const*>(this); else return NULL; }

	Creature* ToCreature() { if (GetTypeId() == TYPEID_UNIT) return reinterpret_cast<Creature*>(this); else return NULL; }
	Creature const* ToCreature() const { if (GetTypeId() == TYPEID_UNIT) return reinterpret_cast<Creature const*>(this); else return NULL; }

	Unit* ToUnit() { if (isType(TYPEMASK_UNIT)) return reinterpret_cast<Unit*>(this); else return NULL; }
	Unit const* ToUnit() const { if (isType(TYPEMASK_UNIT)) return reinterpret_cast<Unit const*>(this); else return NULL; }

	GameObject* ToGameObject() { if (GetTypeId() == TYPEID_GAMEOBJECT) return reinterpret_cast<GameObject*>(this); else return NULL; }
	GameObject const* ToGameObject() const { if (GetTypeId() == TYPEID_GAMEOBJECT) return reinterpret_cast<GameObject const*>(this); else return NULL; }

protected:
	Object();

	void _InitValues();
	void _Create(ObjectGuid const& guid);
	std::string _ConcatFields(uint16 startIndex, uint16 size) const;
	void _LoadIntoDataField(std::string const& data, uint32 startOffset, uint32 count);

	uint32 GetUpdateFieldData(Player const* target, uint32*& flags) const;
	uint32 GetDynamicUpdateFieldData(Player const* target, uint32*& flags) const;

	void BuildMovementUpdate(ByteBuffer* data, uint32 flags) const;
	virtual void BuildValuesUpdate(uint8 updatetype, ByteBuffer* data, Player* target) const;
	virtual void BuildDynamicValuesUpdate(uint8 updatetype, ByteBuffer* data, Player* target) const;

	uint16 m_objectType;

	TypeID m_objectTypeId;
	uint32 m_updateFlag;

	union
	{
		int32  *m_int32Values;
		uint32 *m_uint32Values;
		float  *m_floatValues;
	};

	std::vector<uint32>* _dynamicValues;

	UpdateMask _changesMask;
	UpdateMask _dynamicChangesMask;
	UpdateMask* _dynamicChangesArrayMask;

	uint16 m_valuesCount;
	uint16 _dynamicValuesCount;

	uint16 _fieldNotifyFlags;

	virtual void AddToObjectUpdate() = 0;
	virtual void RemoveFromObjectUpdate() = 0;
	void AddToObjectUpdateIfNeeded();

	bool m_objectUpdated;

private:
	bool m_inWorld;

	PackedGuid m_PackGUID;

	// for output helpfull error messages from asserts
	bool PrintIndexError(uint32 index, bool set) const;
	Object(Object const& right) = delete;
	Object& operator=(Object const& right) = delete;*/
};

#endif