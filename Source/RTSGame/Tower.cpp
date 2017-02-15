#include "RTSGame.h"
#include "Tower.h"

ATower::ATower()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATower::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
