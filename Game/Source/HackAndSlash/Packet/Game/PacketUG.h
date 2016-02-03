#ifndef __PacketUG_H__ 
#define __PacketUG_H__

#pragma once

#include "../../NetLib/NetworkLibrary.h"
#include "../Define.h"

enum eOPCODE_UG
{
	UG_OPCODE_BEGIN = 4000,
	UG_GAME_ENTER_REQ,
	UG_GAME_ENTER_COMPLETE_REQ,
	UG_GAME_MOVEMENT_REQ,
	UG_GAME_MAP_SET_ID_REQ,
	UG_SWITCH_MAP_REQ,
	UG_BACK_TO_MENU_REQ,
	UG_MENU_LOADED_REQ,

	UG_OPCODE_DUMMY,
	UG_OPCODE_END = UG_OPCODE_DUMMY - 1
};

#pragma pack(1)
//------------------------------------------------------------------
BEGIN_PROTOCOL(UG_GAME_ENTER_REQ)
	int mapID;
	int charID;
	Difficulty d;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UG_GAME_ENTER_COMPLETE_REQ)
	int mapID;
	NtlVector postion;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UG_BACK_TO_MENU_REQ)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UG_MENU_LOADED_REQ)

END_PROTOCOL()
#pragma pack()

#endif