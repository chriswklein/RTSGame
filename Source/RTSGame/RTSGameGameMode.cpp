#include "RTSGame.h"
#include "RTSGameGameMode.h"
#include "RTSGamePlayerController.h"

ARTSGameGameMode::ARTSGameGameMode()
{
	PlayerControllerClass = ARTSGamePlayerController::StaticClass();
    DefaultPawnClass = NULL;
}