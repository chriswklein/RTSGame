#include "RTSGame.h"
#include "RTSCharacter.h"

#include "RTSAIController.h"

ARTSCharacter::ARTSCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    AIControllerClass = ARTSAIController::StaticClass();
}