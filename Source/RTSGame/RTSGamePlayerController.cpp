#include "RTSGame.h"
#include "RTSGamePlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"

ARTSGamePlayerController::ARTSGamePlayerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
    bAutoManageActiveCameraTarget = false;
    CameraAccel = 1250.0f;
    CameraDecel = 1000.0f;
    CameraSpeedMax = 100.0f;
    CameraTouchScale = 0.05f;
}

void ARTSGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
    UpdateCamera(DeltaTime);
}

void ARTSGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

    InputComponent->BindAxis("PanCameraVertical", this, &ARTSGamePlayerController::PanCameraVertical);
    InputComponent->BindAxis("PanCameraHorizontal", this, &ARTSGamePlayerController::PanCameraHorizontal);

	// Mobile input
    InputComponent->BindTouch(IE_Pressed, this, &ARTSGamePlayerController::OnTouchBegin);
    InputComponent->BindTouch(IE_Released, this, &ARTSGamePlayerController::OnTouchEnd);
    InputComponent->BindTouch(IE_Repeat, this, &ARTSGamePlayerController::OnTouchMoved);
}

void ARTSGamePlayerController::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if(GetWorld() && GetWorld()->IsGameWorld())
    {
        // Create and assign camera (if not set from level)
        if(TopDownCamera == nullptr)
        {
            FActorSpawnParameters SpawnInfo;
            SpawnInfo.Owner = this;
            SpawnInfo.Instigator = Instigator;
            SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            SpawnInfo.ObjectFlags |= RF_Transient;
            TopDownCamera = GetWorld()->SpawnActor<ACameraActor>(FVector(0.0f, 0.0f, 2500.0f), FRotator(-75.0f, 0.0f, 0.0f), SpawnInfo);
        }
        SetViewTarget(TopDownCamera);
    }
}

void ARTSGamePlayerController::UpdateCamera(float DeltaTime)
{
    if(TopDownCamera)
    {
        CameraVel.X += CameraInputVec.X * CameraAccel * DeltaTime;
        CameraVel.Y += CameraInputVec.Y * CameraAccel * DeltaTime;

        CameraVel = CameraVel.GetClampedToMaxSize(CameraSpeedMax);
        TopDownCamera->AddActorWorldOffset(CameraVel, false);

        if(CameraVel.SizeSquared() > 0.0f)
        {
            const float VelSize = FMath::Max(CameraVel.Size() - (CameraDecel * DeltaTime), 0.f);
            CameraVel = CameraVel.GetSafeNormal() * VelSize;
        }
    }

    CameraInputVec = FVector2D::ZeroVector;
}

void ARTSGamePlayerController::PanCameraVertical(float Val)
{
    CameraInputVec.X += Val;
}

void ARTSGamePlayerController::PanCameraHorizontal(float Val)
{
    CameraInputVec.Y += Val;
}

void ARTSGamePlayerController::OnTouchBegin(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1)
    {
        LastTouchDragLocation = FVector2D(Location);
    }
}

void ARTSGamePlayerController::OnTouchEnd(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1)
    {
        LastTouchDragLocation = FVector2D::ZeroVector;
    }
}

void ARTSGamePlayerController::OnTouchMoved(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1 && !LastTouchDragLocation.IsZero())
    {
        FVector2D const DragDelta = (FVector2D(Location) - LastTouchDragLocation) * CameraTouchScale;

        PanCameraHorizontal(-DragDelta.X);
        PanCameraVertical(DragDelta.Y);

        LastTouchDragLocation = FVector2D(Location);
    }
}