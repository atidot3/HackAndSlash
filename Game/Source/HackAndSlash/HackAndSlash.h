// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __HACKANDSLASH_H__
#define __HACKANDSLASH_H__

#include "Engine.h"
#include "Networking.h"
#include "Online.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "HackAndSlashPlayerController.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Client/Socket/UdpSocketSender.h"
#include "Packet/AllPacket.h"
#include "GenericWindow.h"
#include <string>

DECLARE_LOG_CATEGORY_EXTERN(LogHackAndSlash, Log, All);

class HackAndSlash
{
public:
	bool 					Inited;
	bool 					connected;
	static HackAndSlash		*instance;
	HackAndSlash();
	~HackAndSlash();
	void 					InitPlayer(AHackAndSlashPlayerController *PC);
	void 					InitPlayerGame(AHackAndSlashPlayerController *PC);
	MyUdpSocketSender		*senderSock;
	void 					MyTick();
	bool 					Connect();
	bool 					isConnectedToServer();
	AHackAndSlashPlayerController *getPC(){ return ThePC; }
	// ENGINE
	void 					setGraphicsSettings(int32 _screenSizeX, int32 _screenSizeY, bool _VSync, int32 _WindowMode);
	// PLAYER
	int						AccountID;
	int						money;
	int						charID;
	STATUT_PLAYER			statut;
	// LOGIN
	bool 					Login(FString username, FString password);
	void 					Logout();

	// OTHER NEWTORK THING
	void 					SendGroupInvit(int AccountID);
	void 					AcceptGroupInvit(int AccountID, bool accept);
	void 					QueuePacket(CNtlPacket *pPacket);
	// GAME
	void 					SendEnterWorldReq(int32 mapID, int32 charID, Difficulty diff);
	void 					SendEnterWorldComplete(FVector location, int32 mapID);
	void 					SendMovement(FVector location, int32 mapID);
	void 					SendMapID(int32 mapID);
	void 					SwitchMap();
	void 					BackToMenu();
	void 					MenuLoaded();
public:
	TArray<FFriend>				  TheList;
	TArray<FMaps>				  maps;
	AHackAndSlashPlayerController *ThePC;
	CNtlNetQueue				  recv_queue;
};

#endif
