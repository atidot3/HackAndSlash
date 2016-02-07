#include "stdafx.h"
#include "PacketGRU.h"


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_GRU[] =
{
	DECLARE_PACKET_NAME(GRU_REFRESH_GROUPE_RES),
	DECLARE_PACKET_NAME(GRU_DISBAND_GROUPE_RES),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_GRU(WORD wOpCode)
{
	if (wOpCode < GRU_OPCODE_BEGIN)
	{
		return "NOT DEFINED PACKET NAME";
	}

	if (wOpCode > GRU_OPCODE_END)
	{
		return "NOT DEFINED PACKET NAME";
	}

	int nIndex = wOpCode - GRU_OPCODE_BEGIN;
	if (nIndex >= _countof(s_packetName_GRU))
	{
		return "OPCODE BUFFER OVERFLOW";
	}

	return s_packetName_GRU[nIndex];
}
//------------------------------------------------------------------
