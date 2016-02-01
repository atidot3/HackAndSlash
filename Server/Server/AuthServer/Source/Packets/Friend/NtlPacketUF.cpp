#include "stdafx.h"
#include "NtlPacketUF.h"

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * s_packetName_UF[] =
{
DECLARE_PACKET_NAME(UF_GROUP_FRIEND_REQ),
DECLARE_PACKET_NAME(UF_GROUP_FRIEND_AWSER_REQ),
};
//------------------------------------------------------------------


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UF(WORD wOpCode)
{
if (wOpCode < UF_OPCODE_BEGIN)
{
return "NOT DEFINED PACKET NAME";
}

if (wOpCode > UF_OPCODE_END)
{
return "NOT DEFINED PACKET NAME";
}

int nIndex = wOpCode - UF_OPCODE_BEGIN;
if (nIndex >= _countof(s_packetName_UF))
{
return "OPCODE BUFFER OVERFLOW";
}

return s_packetName_UF[nIndex];
}
//------------------------------------------------------------------
