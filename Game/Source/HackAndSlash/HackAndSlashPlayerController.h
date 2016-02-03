// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "HackAndSlash.h"
#include "Packet/AllPacket.h"
#include "Packet/Define.h"
#include "HackAndSlashPlayerController.generated.h"


/*DECLARE_DYNAMIC_DELEGATE_OneParam(FLoginResult, LoginResultEnum, result);
DECLARE_EVENT(FLayerViewModel, FChangedEvent)*/

UCLASS()
class AHackAndSlashPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AHackAndSlashPlayerController();

protected:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	int32	life;
	UFUNCTION(BlueprintCallable, Category = Game)
	void RefreshMaps();
	UFUNCTION(BlueprintCallable, Category = Game)
	void UpadtePosition(FVector newPosition, int32 mapID);
	UFUNCTION(BlueprintCallable, Category = Connection)
	void LoadingScreen();
	UFUNCTION(BlueprintCallable, Category = Settings)
	void UpdateGraphisme(int32 _screenSizeX, int32 _screenSizeY, bool _VSync, int32 _WindowMode);
	// NETWORK FUNCTION
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Login)
	void LoginResult(LoginResultEnum LoginResult);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FriendsLists)
	void FriendListResult(const TArray<FFriend> &lists);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = FriendsLists)
	void FriendNotificationResult(const bool online, const FString &NameOfFriend);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Characters)
	void CharacterLoadResult(const bool haveCharacter);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void SpawnPlayerParty(const FSpawnFriendParty partyMember);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void MovePlayerParty(const FVector destination, const int32 charID);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void RemovePlayerParty(const int32 charID);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnMapsListRecv(const TArray<FMaps> &maps);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnEnterGameRes(const bool canEnter, const FString &Levelname);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnPopupMessageRes(const FString &TheMessage);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Group)
	void OnKickedFromServer();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Chat)
	void WorldMessageRecv(const FString &sender, const FString &message);
	/*
	
			PARSER FUNCTION
	
	*/

	void parseMyPacket(CNtlPacket *pPacket);

	/*
	
			END
	
	*/
	// LOGIN
	void Login(CNtlPacket * pPacket);
	// CHARACTER
	void RecvCharacterLoad(/*NtlPAcket *pk*/);
	//GAME
	void RecvSpawnPartyMember(CNtlPacket *pPacket);
	void RecvSpawnPartyMemberMovement(CNtlPacket *pPacket);
	void RecvPartyMemberLogout(CNtlPacket *pPacket);
	void RecvMapsList(CNtlPacket *pPacket);
	void RecvPartySwitchMap(CNtlPacket *pPacket);
	void RecvEnterGameRes(CNtlPacket *pPacket);
	void RecvPopupMessage(CNtlPacket *pPacket);
	// OTHER

	// FRIEND
	void RecvFriendList(CNtlPacket * pPacket);
	void RecvInvitForGroup(CNtlPacket * pPacket);
	void RecvRefreshGroup(CNtlPacket * pPacket);
	void RecvFriendNotification(CNtlPacket * pPacket);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnGroupeInviteRecv(const int32 accountID, const FString &name);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnRefreshGroupRecv(const TArray<FRefreshFriend> &friends);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
	void OnRemoveGroupRecv();


	// CHAT
	void RecvWorldMessage(CNtlPacket * pPacket);


	// GAME VARIABLE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Groupe)
	bool isGrouped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Groupe)
	bool isLeader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSession)
	bool isSessionRunning;
};
