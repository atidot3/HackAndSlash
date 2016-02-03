#pragma once

#include "NtlPacketCommon.h"
#include "CSArchitecture.h"



//------------------------------------------------------------------
// Packet Enumeration
//------------------------------------------------------------------
enum eOPCODE_UGR
{
	UGR_OPCODE_BEGIN = 400,

	UGR_HEARTBEAT = UGR_OPCODE_BEGIN,

	UGR_GROUPE_KICK,

	UGR_OPCODE_DUMMY,
	UGR_OPCODE_END = UGR_OPCODE_DUMMY - 1
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UGR(WORD wOpCode);
//------------------------------------------------------------------



#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(UGR_GROUPE_KICK) // SEND ALL GROUPE LIST
	int friendAccountID;
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()