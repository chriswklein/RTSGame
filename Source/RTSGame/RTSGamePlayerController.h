#pragma once
#include "GameFramework/PlayerController.h"
#include "RTSGamePlayerController.generated.h"

UCLASS()
class ARTSGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSGamePlayerController();

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
    virtual void PostInitializeComponents() override;
	// End PlayerController interface

private:
    void UpdateCamera(float DeltaTime);

    void PanCameraVertical(float Val);
    void PanCameraHorizontal(float Val);

    void OnTouchBegin(const ETouchIndex::Type FingerIndex, const FVector Location);
    void OnTouchEnd(const ETouchIndex::Type FingerIndex, const FVector Location);
    void OnTouchMoved(const ETouchIndex::Type FingerIndex, const FVector Location);

    /** Camera acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true", ClampMin = "100", ClampMax = "5000"))
	float CameraAccel;

    /** Camera deceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true", ClampMin = "100", ClampMax = "5000"))
	float CameraDecel;

    /** Maximum camera speed (per second) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true", ClampMin = "50", ClampMax = "500"))
	float CameraSpeedMax;

    /** Scale touch input camera panning */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true", ClampMin = "0.05", ClampMax = "1.0"))
    float CameraTouchScale;

	/** Main camera view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class ACameraActor* TopDownCamera;

    FVector CameraVel;
    FVector2D CameraInputVec;
    FVector2D LastTouchDragLocation;
};