#pragma once

#include "NtlPacketCommon.h"
#include "CSArchitecture.h"

enum eOPCODE_FU
{
	FU_OPCODE_BEGIN = 300,

	FU_FRIENDLIST_RES = FU_OPCODE_BEGIN,

	FU_ADD_FRIEND_GROUPE_RES,
	FU_GROUP_FRIEND_REFUSE_RES,
	FU_GROUP_FRIEND_REFRESH_RES,
	FU_FRIEND_NOTIFICATION_RES,
	FU_FRIEND_REQUEST_RES,
	FU_FRIEND_REQUEST_RECV_RES,
	FU_FRIEND_PENDING_RECV_LIST_RES,

	FU_OPCODE_DUMMY,
	FU_OPCODE_END = FU_OPCODE_DUMMY - 1
};

//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_FU(WORD wOpCode);
//------------------------------------------------------------------

#pragma pack(1)
struct Friend
{
	char		name[20];
	bool		online;
	int			accountID;
};
struct PendingRequest
{
	char		name[20];
	int			accountID;
};
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_FRIENDLIST_RES) // SEND ALL FRIEND LIST
	int			totalFriend;
	Friend		friends[50];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_GROUP_FRIEND_REFUSE_RES) // REFUSE THE INVITATION
	WORD		wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_ADD_FRIEND_GROUPE_RES) // SEND TO THE PLAYER THE GROUPE REQUEST
	int			friendAccountID;
	char		name[20];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_FRIEND_NOTIFICATION_RES) // SEND TO THE PLAYER THE GROUPE REQUEST
	Friend		friends;
	WORD		wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_FRIEND_REQUEST_RES) // SEND TO THE PLAYER THE GROUPE REQUEST RESPONSE
	WORD		wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_FRIEND_REQUEST_RECV_RES) // SEND TO THE PLAYER THE GROUPE REQUEST REQUEST
	char		from[20];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(FU_FRIEND_PENDING_RECV_LIST_RES) // SEND TO THE PLAYER THE GROUPE REQUEST REQUEST
	PendingRequest	resquests[20];
	int				lenght;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()