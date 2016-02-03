#pragma once

#include "Character.h"

enum eOPCODE_CU
{
	CU_OPCODE_BEGIN = 3000,

	CU_HEARTBEAT = CU_OPCODE_BEGIN,

	CU_CHARACTER_ADD_RES,
	CU_CHARACTER_DEL_RES,
	CU_CHARACTER_SELECT_RES,
	CU_CHARACTER_LOAD_RES,
	
	CU_OPCODE_DUMMY,
	CU_OPCODE_END = CU_OPCODE_DUMMY - 1
};

#pragma pack(1)

struct CU_CHARACTER_ADD_RESPONCE
{
	int				wResultCode;
	sPC_SUMMARY		sPcDataSummary;
};
struct CU_CHARACTER_DEL_RESPONCE
{
	int				wResultCode;
	int				charId;
	//sDBO_TIME		tDeleteDate;
};
struct 	CU_CHARACTER_SELECT_RESPONCE
{
	int				wResultCode;
	int				charId;
	int				abyAuthKey[MAX_SIZE_AUTH_KEY];
	char			szGameServerIP[MAX_LENGTH_OF_IP + 1];
	int				wGameServerPortForClient;
};
struct CU_CHARACTER_LOAD_RESPONCE
{
	//sDELETE_WAIT_CHARACTER_INFO asDelData[NTL_MAX_COUNT_USER_CHAR_SLOT];
	int				byCount;
	sPC_SUMMARY		sPcData[MAX_COUNT_USER_CHAR_SLOT]; // Maximum of Character is 8 (Temporary)	
};
#pragma pack()