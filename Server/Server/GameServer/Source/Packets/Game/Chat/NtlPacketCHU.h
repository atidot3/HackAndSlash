#ifndef __PacketCHU_H__ 
#define __PacketCHU_H__

#pragma once
#include "NtlPacketCommon.h"
#include "CSArchitecture.h"
#include "../../Game/Groupe/Groupe.h"

enum eOPCODE_CHU
{
	CHU_OPCODE_BEGIN = 700,

	CHU_SEND_WORLD_MESSAGE_RES,

	CHU_OPCODE_DUMMY,
	CHU_OPCODE_END = CHU_OPCODE_DUMMY - 1
};
//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_CHU(WORD wOpCode);
//------------------------------------------------------------------
#pragma pack(1)
//------------------------------------------------------------------
BEGIN_PROTOCOL(CHU_SEND_WORLD_MESSAGE_RES)
	WCHAR		Sender[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR		Message[NTL_MAX_LENGTH_OF_CHAT_MESSAGE + 1];
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()

#endif