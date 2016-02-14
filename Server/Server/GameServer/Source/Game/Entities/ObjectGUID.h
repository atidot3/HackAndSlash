#ifndef ObjectGuid_h__
#define ObjectGuid_h__

#include <type_traits>
#include <functional>
#include <set>
#include <string>
#include <sstream>
#include <stdint.h>
#include <vector>

#include <WinSock2.h>

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

enum TypeID
{
	TYPEID_OBJECT = 0,
	TYPEID_ITEM = 1,
	TYPEID_CONTAINER = 2,
	TYPEID_UNIT = 3,
	TYPEID_PLAYER = 4,
	TYPEID_GAMEOBJECT = 5,
	TYPEID_DYNAMICOBJECT = 6,
	TYPEID_CORPSE = 7,
	TYPEID_AREATRIGGER = 8,
	TYPEID_SCENEOBJECT = 9,
	TYPEID_CONVERSATION = 10
};

#endif