#include "RTSGame.h"
#include "RTSTower.h"

ARTSTower::ARTSTower()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARTSTower::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
