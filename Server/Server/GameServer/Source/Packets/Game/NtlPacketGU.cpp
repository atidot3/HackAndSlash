#include "stdafx.h"
#include "PacketGU.h"


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_GU[] =
{
	DECLARE_PACKET_NAME(GU_REFRESH_GROUPE_RES),
	DECLARE_PACKET_NAME(GU_DISBAND_GROUPE_RES),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_GU(WORD wOpCode)
{
	if (wOpCode < GU_OPCODE_BEGIN)
	{
		return "NOT DEFINED PACKET NAME";
	}

	if (wOpCode > GU_OPCODE_END)
	{
		return "NOT DEFINED PACKET NAME";
	}

	int nIndex = wOpCode - GU_OPCODE_BEGIN;
	if (nIndex >= _countof(s_packetName_GU))
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_GU[nIndex];
}
//------------------------------------------------------------------
