#pragma once
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

UCLASS(Blueprintable)
class ATower : public APawn
{
	GENERATED_BODY()

public:
    ATower();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:
};

