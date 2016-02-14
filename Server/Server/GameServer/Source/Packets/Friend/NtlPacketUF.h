#pragma once

#include "NtlPacketCommon.h"
#include "CSArchitecture.h"

enum eOPCODE_UF
{
	UF_OPCODE_BEGIN = 200,

	UF_GROUP_FRIEND_REQ = UF_OPCODE_BEGIN,
	UF_GROUP_FRIEND_AWSER_REQ,
	UF_REQUEST_NEW_FRIEND_REQ,

	UF_OPCODE_DUMMY,
	UF_OPCODE_END = UF_OPCODE_DUMMY - 1
};

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UF(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)
//------------------------------------------------------------------
BEGIN_PROTOCOL(UF_GROUP_FRIEND_REQ) // PLAYER SENDED A REQUEST TO A PLAYER
	int friendAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UF_GROUP_FRIEND_AWSER_REQ) // THE AWSER FROM THE PLAYER
	int friendAccountID;
	bool accept;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UF_REQUEST_NEW_FRIEND_REQ) // PLAYER SENDED A REQUEST TO A PLAYER
	char toWho[20];
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()