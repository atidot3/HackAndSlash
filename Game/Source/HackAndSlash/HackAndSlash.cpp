// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "HackAndSlash.h"


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, HackAndSlash, "HackAndSlash" );
DEFINE_LOG_CATEGORY(LogHackAndSlash)

HackAndSlash *HackAndSlash::instance = new HackAndSlash();
 
HackAndSlash::HackAndSlash()
{
	Inited = false;
	connected = false;
}
HackAndSlash::~HackAndSlash()
{

}
void HackAndSlash::InitPlayerGame(AHackAndSlashPlayerController *PC)
{
	statut = STATUT_PLAYER::OK;
	ThePC = PC;
	if (senderSock != nullptr)
		senderSock->setController(PC);
}
void HackAndSlash::InitPlayer(AHackAndSlashPlayerController *PC)
{
	if (PC != nullptr)
	{
		if (Inited == false || senderSock == nullptr)
			senderSock = new MyUdpSocketSender();
		ThePC = PC;
		senderSock->setController(PC);
	}
}
void HackAndSlash::QueuePacket(CNtlPacket *pPacket)
{
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();

	if (pHeader->wOpCode >= GU_OPCODE_BEGIN && pHeader->wOpCode <= GU_OPCODE_END && statut == STATUT_PLAYER::OK)
	{
		if (ThePC != NULL && ThePC != nullptr)
		{
			if (IsValid(ThePC) == true)
			{
				ThePC->parseMyPacket(pPacket);
				return;
			}
		}
	}
	recv_queue.PushPacket(pPacket);
}
void HackAndSlash::MyTick()
{
	if (ThePC != NULL && ThePC != nullptr)
	{
		if (statut != STATUT_PLAYER::LOADINGSCREEN)
		{
			if (IsValid(ThePC) == true)
			{
				if (recv_queue.IsEmpty() == false)
				{
					ThePC->parseMyPacket(recv_queue.PopPacket());
				}
			}
		}
	}
}
void HackAndSlash::setGraphicsSettings(int32 _screenSizeX, int32 _screenSizeY, bool _VSync, int32 _WindowMode)
{
	if (GEngine->GetGameUserSettings() != nullptr)
	{
		GEngine->GetGameUserSettings()->SetVSyncEnabled(_VSync);
		FIntPoint screenSize;
		screenSize.X = _screenSizeX;
		screenSize.Y = _screenSizeY;
		GEngine->GetGameUserSettings()->SetScreenResolution(screenSize);
		GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(_WindowMode));
		GEngine->GameUserSettings->ApplyResolutionSettings(true);
		GEngine->GetGameUserSettings()->ApplySettings();
		Scalability::SaveState(GGameUserSettingsIni);
		GEngine->GetGameUserSettings()->SaveSettings();
		//GEngine->GetGameUserSettings()->SetAudioQualityLevel(0);
	}
}
bool HackAndSlash::isConnectedToServer()
{
	return connected;
}
bool HackAndSlash::Connect()
{
	if (Inited == false)
	{
		if (ThePC != nullptr)
		{
			if (senderSock == nullptr)
				senderSock = new MyUdpSocketSender();
			senderSock->setController(ThePC);
			if (senderSock->Init() != true)
				return false;
		}
	}
	if (connected == false)
	{
		connected = senderSock->Connect();
		return connected;
	}
	return connected;
}
bool HackAndSlash::Login(FString username, FString password)
{
	Inited = true;
	std::string cstr(TCHAR_TO_UTF8(*username)); 
	std::string cstr2(TCHAR_TO_UTF8(*password));
	return senderSock->Login(cstr.c_str(), cstr2.c_str());
}
void HackAndSlash::Logout()
{
	if (senderSock != nullptr)
		senderSock->Logout();
	Inited = false;
	connected = false;
	if (senderSock != nullptr)
	{
		delete senderSock;
	}
	recv_queue.Clear();
}
void HackAndSlash::SendEnterWorldReq(int32 mapID, int32 charID, Difficulty diff)
{
	senderSock->SendEnterWorldReq(mapID, charID, diff);
}
void HackAndSlash::SendEnterWorldComplete(FVector location, int32 mapID)
{
	NtlVector position;
	position.x = location.X;
	position.y = location.Y;
	position.z = location.Z;
	senderSock->SendEnterGameComplete(position, mapID);
}
void HackAndSlash::SendMovement(FVector location, int32 mapID)
{
	NtlVector Newlocation;

	Newlocation.x = location.X;
	Newlocation.y = location.Y;
	Newlocation.z = location.Z;
	senderSock->SendMovement(Newlocation, mapID);
}
void HackAndSlash::SendMapID(int32 mapID)
{
	senderSock->SendMapID(mapID);
}
void HackAndSlash::SwitchMap()
{
	senderSock->SwitchMap(charID);
}
void HackAndSlash::SendGroupInvit(int _AccountID)
{
	senderSock->SendGroupInvit(_AccountID);
}
void HackAndSlash::AcceptGroupInvit(int _AccountID, bool accept)
{
	senderSock->AcceptGroupInvit(_AccountID, accept);
}
void HackAndSlash::BackToMenu()
{
	statut = STATUT_PLAYER::LOADINGSCREEN;
	senderSock->BackToMenu();
}
void HackAndSlash::MenuLoaded()
{
	senderSock->MenuLoaded();
}