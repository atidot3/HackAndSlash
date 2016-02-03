#ifndef __PacketAU_H__ 
#define __PacketAU_H__ 

#pragma once

#include "../../NetLib/NetworkLibrary.h"
#include "../Define.h"

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

const char * NtlGetPacketName_AU(WORD wOpCode);

#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(AU_LOGIN_RES)
	WORD				wResultCode;
	BYTE				abyAuthKey[NTL_MAX_SIZE_AUTH_KEY];
	ACCOUNTID			accountId;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()

struct AU_Packet_RES
{
	int resultCode;
	int accountID;
	char AUTH_KEY[73];
	int money;
};
/*
struct AU_FriendList_RES
{
	int totalFriend;
	Friend friends[50];
};
struct AU_Friend_GroupRES
{
	int FriendAccountID;
	char name[20];
};
struct AU_FRIEND_GROUP_REFUSE_RES
{
	char name[20];
};
struct AU_FRIEND_GROUP
{
	int charID;
	char name[20];
	bool leader;
	int classe;
	int level;
	int life;
	int accountID;
};
struct AU_FRIEND_GROUP_REFRESH_RES
{
	int size;
	AU_FRIEND_GROUP group[5];
};*/
#pragma pack()

#endif