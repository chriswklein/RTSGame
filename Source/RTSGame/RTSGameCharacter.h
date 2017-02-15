#pragma once
#include "GameFramework/Character.h"
#include "RTSGameCharacter.generated.h"

UCLASS(Blueprintable)
class ARTSGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARTSGameCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
};

