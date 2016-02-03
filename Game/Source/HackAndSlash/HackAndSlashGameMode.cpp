// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "HackAndSlash.h"
#include "HackAndSlashGameMode.h"
#include "HackAndSlashPlayerController.h"
#include "HackAndSlashCharacter.h"

AHackAndSlashGameMode::AHackAndSlashGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHackAndSlashPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
