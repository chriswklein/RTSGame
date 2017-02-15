#pragma once
#include "AIController.h"
#include "RTSGameAIController.generated.h"

UCLASS(Blueprintable)
class ARTSGameAIController : public AAIController
{
	GENERATED_BODY()

public:
    ARTSGameAIController();
    virtual void Tick(float DeltaTime) override;
};

