#pragma once

#include "Character.h"

enum eOPCODE_UC
{
	UC_OPCODE_BEGIN = 2000,

	UC_CHARACTER_SERVERLIST_REQ = UC_OPCODE_BEGIN,
	UC_CHARACTER_ADD_REQ,
	UC_CHARACTER_DEL_REQ,
	UC_CHARACTER_SELECT_REQ,
	
	UC_OPCODE_DUMMY,
	UC_OPCODE_END = UC_OPCODE_DUMMY - 1
};

#pragma pack(1)

struct UC_CHARACTER_ADD_REQUEST
{
	char					awchCharName[MAX_SIZE_CHAR_NAME + 1];
	int						dwCodePage;
	int						byRace;
	int						byClass;
	int						byGender;
	int						byFace;
	int						byHair;
	int						byHairColor;
	int						bySkinColor;
	int						byBlood;
};

struct UC_CHARACTER_DEL_REQUEST
{
	int		charId;
};
struct UC_CHARACTER_SELECT_REQUEST
{
	int			charId;
	int		    byServerChannelIndex;
};

#pragma pack()