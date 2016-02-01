#include "stdafx.h"
#include "NtlPacketFU.h"


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_FU[] =
{
	DECLARE_PACKET_NAME(FU_FRIENDLIST_RES),
	DECLARE_PACKET_NAME(FU_ADD_FRIEND_GROUPE_RES),
	DECLARE_PACKET_NAME(FU_GROUP_FRIEND_REFUSE_RES),
	DECLARE_PACKET_NAME(FU_GROUP_FRIEND_REFRESH_RES),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_FU(WORD wOpCode)
{
	if (wOpCode < FU_OPCODE_BEGIN)
	{
		return "NOT DEFINED PACKET NAME";
	}

	if (wOpCode > FU_OPCODE_END)
	{
		return "NOT DEFINED PACKET NAME";
	}

	int nIndex = wOpCode - FU_OPCODE_BEGIN;
	if (nIndex >= _countof(s_packetName_FU))
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_FU[nIndex];
}
//------------------------------------------------------------------
