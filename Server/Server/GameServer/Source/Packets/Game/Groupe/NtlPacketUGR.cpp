#include "stdafx.h"
#include "PacketUGR.h"

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_UGR[] =
{
	DECLARE_PACKET_NAME(0),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UGR(WORD wOpCode)
{
if (wOpCode < UGR_OPCODE_BEGIN)
{
return "NOT DEFINED PACKET NAME";
}

if (wOpCode > UGR_OPCODE_END)
{
return "NOT DEFINED PACKET NAME";
}

int nIndex = wOpCode - UGR_OPCODE_BEGIN;
if (nIndex >= _countof(s_packetName_UGR))
{
return "OPCODE BUFFER OVERFLOW";
}

return s_packetName_UGR[nIndex];
}
//------------------------------------------------------------------
