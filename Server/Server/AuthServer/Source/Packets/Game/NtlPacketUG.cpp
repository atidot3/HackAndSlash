#include "stdafx.h"
#include "PacketUG.h"

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_UG[] =
{
	DECLARE_PACKET_NAME(0),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UG(WORD wOpCode)
{
if (wOpCode < UG_OPCODE_BEGIN)
{
return "NOT DEFINED PACKET NAME";
}

if (wOpCode > UG_OPCODE_END)
{
return "NOT DEFINED PACKET NAME";
}

int nIndex = wOpCode - UG_OPCODE_BEGIN;
if (nIndex >= _countof(s_packetName_UG))
{
return "OPCODE BUFFER OVERFLOW";
}

return s_packetName_UG[nIndex];
}
//------------------------------------------------------------------
