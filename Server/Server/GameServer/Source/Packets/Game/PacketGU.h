#ifndef __PacketGU_H__ 
#define __PacketGU_H__

#pragma once
#include "NtlPacketCommon.h"
#include "CSArchitecture.h"
#include "../../Game/Groupe/Groupe.h"

enum eOPCODE_GU
{
	GU_OPCODE_BEGIN = 5000,

	GU_LOGIN_RES,
	GU_ENTER_GAME_RES,
	GU_PARTY_MEMBER_SPAWN,
	GU_PARTY_MEMBER_MOVE,
	GU_PARTY_MEMBER_LOGOUT,
	GU_LOAD_MAPS,
	GU_PARTY_SWITCH_MAP,
	GU_POPUP_MESSAGE,

	GU_OPCODE_END_DUMMY,
	GU_OPCODE_END = GU_OPCODE_END_DUMMY - 1
};

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_GU(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)
struct Maps
{
	int id;
	char name[20];
};
struct GU_PARTY_MEMBER_DATA
{
	int level;
	int charId;
	NtlVector location;
	char name[20];
};
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_LOGIN_RES)
	WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ENTER_GAME_RES)
	WORD				wResultCode;
	char				mapName[50];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_LOAD_MAPS)
	Maps	map[50];
	int		byCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_SPAWN)
	int count;
	GU_PARTY_MEMBER_DATA group[5];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_LOGOUT)
	int charID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_MOVE)
	int charID;
	NtlVector location;
	int mapID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_POPUP_MESSAGE)
	BYTE	theMessage[NTL_MAX_LENGTH_OF_CHAT_MESSAGE];
END_PROTOCOL()
#pragma pack()

#endif