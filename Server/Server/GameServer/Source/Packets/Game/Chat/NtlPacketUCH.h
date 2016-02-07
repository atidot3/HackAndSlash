#ifndef __PacketUCH_H__ 
#define __PacketUCH_H__

#pragma once
#include "NtlPacketCommon.h"
#include "CSArchitecture.h"
#include "../../Game/Groupe/Groupe.h"

enum eOPCODE_UCH
{
	UCH_OPCODE_BEGIN = 600,

	UCH_SEND_WORLD_MESSAGE,

	UCH_OPCODE_DUMMY,
	UCH_OPCODE_END = UCH_OPCODE_DUMMY - 1
};
//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UCH(WORD wOpCode);
//------------------------------------------------------------------
#pragma pack(1)
//------------------------------------------------------------------
BEGIN_PROTOCOL(UCH_SEND_WORLD_MESSAGE)
	ACCOUNTID	Sender;
	WCHAR		Message[NTL_MAX_LENGTH_OF_CHAT_MESSAGE + 1];
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()

#endif