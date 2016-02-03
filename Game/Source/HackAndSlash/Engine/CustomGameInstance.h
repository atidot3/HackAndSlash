// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	bool StartOnlineGame(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
};
