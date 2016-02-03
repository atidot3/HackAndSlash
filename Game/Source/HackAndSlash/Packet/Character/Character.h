#ifndef character_h
#define character_h

#pragma once

#include <vector>
#include "Avatar.h"

#define MIN_SIZE_CHAR_NAME_UNICODE					(2)
#define MAX_SIZE_CHAR_NAME							(16)
#define MAX_SIZE_AUTH_KEY							(16)
#define MAX_LENGTH_OF_IP							(64)
#define MAX_COUNT_USER_CHAR_SLOT					(8)
#define MAX_EQUIP_ITEM_SLOT							(12)

typedef unsigned int TBLIDX;
const TBLIDX INVALID_TBLIDX = 0xFFFFFFFF;

struct sVECTOR3
{
	float x;
	float y;
	float z;
};

enum eEQUIP_SLOT_TYPE
{
	EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_SUB_WEAPON,
	EQUIP_SLOT_TYPE_JACKET,
	EQUIP_SLOT_TYPE_PANTS,
	EQUIP_SLOT_TYPE_BOOTS,
	EQUIP_SLOT_TYPE_SCOUTER,
	EQUIP_SLOT_TYPE_COSTUME,
	EQUIP_SLOT_TYPE_NECKLACE,
	EQUIP_SLOT_TYPE_EARRING_1,
	EQUIP_SLOT_TYPE_EARRING_2,
	EQUIP_SLOT_TYPE_RING_1,
	EQUIP_SLOT_TYPE_RING_2,

	EQUIP_SLOT_TYPE_COUNT,
	EQUIP_SLOT_TYPE_UNKNOWN = 0xFF,

	EQUIP_SLOT_TYPE_FIRST = EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_LAST = EQUIP_SLOT_TYPE_RING_2,
};

struct sPC_DATA
{
	int				charId;
	char			awchName[MAX_SIZE_CHAR_NAME + 1];

	int				byClass;

	float			fPositionX;
	float			fPositionY;
	float			fPositionZ;

	float			fDirX;
	float			fDirY;
	float			fDirZ;

	int				worldId;
	int				dwEXP;
	int				byLevel;
	int				dwLP;
	int				dwEP;
	int				dwRP;
};
struct sPC_SUMMARY
{
	int				charId;
	char			awchName[MAX_SIZE_CHAR_NAME + 1];
	int				byClass;
	int				byLevel;
	int				worldId;
	float			fPositionX;
	float			fPositionY;
	float			fPositionZ;
};
struct sPC_PROFILE
{
	int					charId;
	char				awchName[MAX_SIZE_CHAR_NAME + 1];
	sAVATAR_ATTRIBUTE	avatarAttribute;
	int					wCurLP;
	int					wCurEP;
	int					wCurRP;
	int					byLevel;
	int					dwCurExp;
	int					dwMaxExpInThisLevel;
};
#endif