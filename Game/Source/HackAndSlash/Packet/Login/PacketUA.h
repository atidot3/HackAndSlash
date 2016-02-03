#ifndef __PacketUA_H__ 
#define __PacketUA_H__ 

#pragma once

#include "../../NetLib/NetworkLibrary.h"

enum eOPCODE_UA
{
	UA_OPCODE_BEGIN = 100,

	UA_LOGIN_REQ = UA_OPCODE_BEGIN,
	UA_LOGIN_REQ_KOREA_CJ,

	UA_LOGIN_CREATEUSER_REQ,
	UA_LOGIN_DISCONNECT_REQ,

	UA_OPCODE_DUMMY,
	UA_OPCODE_END = UA_OPCODE_DUMMY - 1
};

#pragma pack(1)
//------------------------------------------------------------------
BEGIN_PROTOCOL(UA_LOGIN_REQ)
WCHAR		awchUserId[12 + 1];
WCHAR		awchPasswd[12 + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UA_LOGIN_DISCONNECT_REQ)

END_PROTOCOL()
struct UA_Packet_REQ
{
	char username[512];
	char password[512];
};
struct UA_Friend_Groupe_REQ
{
	int friendAccountID;
	int AccountID;
	char AUTH_KEY[73];
};
struct UA_FRIEND_GROUPE_AWSER_REQ
{
	int friendAccountID;
	int AccountID;
	char AUTH_KEY[73];
	bool accept;
};
#pragma pack()

#endif