// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HackAndSlashLoadingScreen.h"

AHackAndSlashPlayerController::AHackAndSlashPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	isGrouped = false;
	isLeader = false;
	isSessionRunning = false;
}
void AHackAndSlashPlayerController::UpdateGraphisme(int32 _screenSizeX, int32 _screenSizeY, bool _VSync, int32 _WindowMode)
{
	HackAndSlash::instance->setGraphicsSettings(_screenSizeX, _screenSizeY, _VSync, _WindowMode);
}
void AHackAndSlashPlayerController::UpadtePosition(FVector newPosition, int32 mapID)
{
	HackAndSlash::instance->SendMovement(newPosition, mapID);
}
void AHackAndSlashPlayerController::LoginResult_Implementation(LoginResultEnum LoginResult)
{
}
void AHackAndSlashPlayerController::FriendListResult_Implementation(const TArray<FFriend> &lists)
{
}
void AHackAndSlashPlayerController::FriendNotificationResult_Implementation(const bool online, const FString &NameOfFriend)
{
}
void AHackAndSlashPlayerController::CharacterLoadResult_Implementation(const bool haveCharacter)
{
}
void AHackAndSlashPlayerController::SpawnPlayerParty_Implementation(const FSpawnFriendParty partyMember)
{
}
void AHackAndSlashPlayerController::MovePlayerParty_Implementation(const FVector destination, const int32 charID)
{
}
void AHackAndSlashPlayerController::RemovePlayerParty_Implementation(const int32 charID)
{
}
void AHackAndSlashPlayerController::OnMapsListRecv_Implementation(const TArray<FMaps> &maps)
{
}
void AHackAndSlashPlayerController::OnGroupeInviteRecv_Implementation(const int32 accountID, const FString &name)
{
}
void AHackAndSlashPlayerController::OnRefreshGroupRecv_Implementation(const TArray<FRefreshFriend> &friends)
{
}
void AHackAndSlashPlayerController::OnRemoveGroupRecv_Implementation()
{
}
void AHackAndSlashPlayerController::OnEnterGameRes_Implementation(const bool canEnter, const FString &Levelname)
{
}
void AHackAndSlashPlayerController::OnPopupMessageRes_Implementation(const FString &TheMessage)
{
}
void AHackAndSlashPlayerController::OnKickedFromServer_Implementation()
{
}
void AHackAndSlashPlayerController::WorldMessageRecv_Implementation(const FString &sender, const FString &message)
{
}
void AHackAndSlashPlayerController::LoadingScreen()
{
	HackAndSlash::instance->statut = STATUT_PLAYER::LOADINGSCREEN;
	IHackAndSlashLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<IHackAndSlashLoadingScreenModule>("HackAndSlashLoadingScreen");
	if (LoadingScreenModule != nullptr)
	{
		LoadingScreenModule->StartInGameLoadingScreen();
	}
}