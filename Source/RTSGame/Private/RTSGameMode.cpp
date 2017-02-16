#include "RTSGame.h"
#include "RTSGameMode.h"
#include "RTSPlayerController.h"

ARTSGameMode::ARTSGameMode()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
    DefaultPawnClass = NULL;
}