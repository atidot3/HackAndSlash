#ifndef __AllPacket_h__ 
#define __AllPacket_h__ 

#include "../NetLib/NetworkLibrary.h"
#include "Login/PacketAU.h"
#include "Login/PacketUA.h"
#include "ResultCode.h"
#include "Define.h"
#include "Character/Avatar.h"
#include "Character/NtlPacketUC.h"
#include "Character/Character.h"
#include "Character/NtlPacketCU.h"
#include "Game/PacketUG.h"
#include "Game/PacketGU.h"
#include "Friend/NtlPacketUF.h"
#include "Friend/NtlPacketFU.h"
#include "Game/Groupe/PacketUGR.h"
#include "Game/Groupe/PacketGRU.h"


/*
********* CREATURE FLAG	**********
1	Gossip
2	Quest Giver
3	Trainer
4	Vendor
5	Teleporter
6	Banker
7	Enemy
*/

/*
struct NtlPAcket
{
	int enume;
	char pk[4096];
};*/

#endif