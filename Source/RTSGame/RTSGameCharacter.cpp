// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "RTSGame.h"
#include "RTSGameCharacter.h"

ARTSGameCharacter::ARTSGameCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

}

void ARTSGameCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
