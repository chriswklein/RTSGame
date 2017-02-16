#pragma once
#include "GameFramework/Pawn.h"
#include "RTSTower.generated.h"

UCLASS(Blueprintable)
class ARTSTower : public APawn
{
	GENERATED_BODY()

public:
    ARTSTower();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
};

