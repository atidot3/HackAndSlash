#pragma once

#include "../../../NetLib/NetworkLibrary.h"

//------------------------------------------------------------------
// Packet Enumeration
//------------------------------------------------------------------
enum eOPCODE_UGR
{
	UGR_OPCODE_BEGIN = 400,

	UGR_HEARTBEAT = UGR_OPCODE_BEGIN,



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

//------------------------------------------------------------------

#pragma pack()