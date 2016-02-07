#pragma once

#include "NtlPacketCommon.h"
#include "CSArchitecture.h"

//------------------------------------------------------------------
// Packet Enumeration
//------------------------------------------------------------------

const DWORD					MAX_NUMOF_SERVER_DB = 10;

enum eOPCODE_AU
{
	AU_OPCODE_BEGIN = 1000,

	AU_HEARTBEAT = AU_OPCODE_BEGIN,
	AU_LOGIN_RES,
	AU_LOGIN_CREATEUSER_RES,
	AU_LOGIN_DISCONNECT_RES,

	AU_OPCODE_DUMMY,
	AU_OPCODE_END = AU_OPCODE_DUMMY - 1
};

struct sSERVERDB
{
	int			id;
	char		ip[16];
	int			port;
	char		servername[16];
	int			len;
};


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_AU(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_HEARTBEAT)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_RES)
	WORD				wResultCode;
	BYTE				abyAuthKey[NTL_MAX_SIZE_AUTH_KEY];
	ACCOUNTID			accountId;
	sSERVERDB			serverList[MAX_NUMOF_SERVER_DB];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_CREATEUSER_RES)
	WORD		wResultCode;
	WCHAR		awchUserId[NTL_MAX_SIZE_USERID_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_DISCONNECT_RES)
END_PROTOCOL()
//------------------------------------------------------------------

#pragma pack()