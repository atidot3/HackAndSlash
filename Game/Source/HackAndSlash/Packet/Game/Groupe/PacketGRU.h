#pragma once

#include "../../../NetLib/NetworkLibrary.h"

//------------------------------------------------------------------
// Packet Enumeration
//------------------------------------------------------------------
enum eOPCODE_GRU
{
	GRU_OPCODE_BEGIN = 500,

	GRU_HEARTBEAT = GRU_OPCODE_BEGIN,
	
	GRU_REFRESH_GROUPE_RES,
	GRU_DISBAND_GROUPE_RES,

	GRU_OPCODE_DUMMY,
	GRU_OPCODE_END = GRU_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_GRU(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)

struct AU_FRIEND_GROUP
{
	int charID;
	char name[20];
	bool leader;
	int classe;
	int level;
	int life;
	int accountID;
	bool disconnected;
};

//------------------------------------------------------------------
BEGIN_PROTOCOL(GRU_REFRESH_GROUPE_RES) // SEND ALL GROUPE LIST
	int size;
	AU_FRIEND_GROUP	groupePlayers[5];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GRU_DISBAND_GROUPE_RES) // SEND ALL GROUPE LIST
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()