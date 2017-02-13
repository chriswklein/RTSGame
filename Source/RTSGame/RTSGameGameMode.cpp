// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "RTSGame.h"
#include "RTSGameGameMode.h"
#include "RTSGamePlayerController.h"
#include "RTSGameCharacter.h"

ARTSGameGameMode::ARTSGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}