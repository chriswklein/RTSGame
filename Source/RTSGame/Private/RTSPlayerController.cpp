#include "RTSGame.h"
#include "RTSPlayerController.h"

ARTSPlayerController::ARTSPlayerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
    bAutoManageActiveCameraTarget = false;
    CameraAccel = 1250.0f;
    CameraDecel = 1000.0f;
    CameraSpeedMax = 100.0f;
    CameraTouchScale = 0.05f;
}

void ARTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
    UpdateCamera(DeltaTime);
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

    InputComponent->BindAxis("PanCameraVertical", this, &ARTSPlayerController::PanCameraVertical);
    InputComponent->BindAxis("PanCameraHorizontal", this, &ARTSPlayerController::PanCameraHorizontal);

	// Mobile input
    InputComponent->BindTouch(IE_Pressed, this, &ARTSPlayerController::OnTouchBegin);
    InputComponent->BindTouch(IE_Released, this, &ARTSPlayerController::OnTouchEnd);
    InputComponent->BindTouch(IE_Repeat, this, &ARTSPlayerController::OnTouchMoved);
}

void ARTSPlayerController::PostInitializeComponents()
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

void ARTSPlayerController::UpdateCamera(float DeltaTime)
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

void ARTSPlayerController::PanCameraVertical(float Val)
{
    CameraInputVec.X += Val;
}

void ARTSPlayerController::PanCameraHorizontal(float Val)
{
    CameraInputVec.Y += Val;
}

void ARTSPlayerController::OnTouchBegin(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1)
    {
        LastTouchDragLocation = FVector2D(Location);
    }
}

void ARTSPlayerController::OnTouchEnd(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1)
    {
        LastTouchDragLocation = FVector2D::ZeroVector;
    }
}

void ARTSPlayerController::OnTouchMoved(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if(FingerIndex == ETouchIndex::Touch1 && !LastTouchDragLocation.IsZero())
    {
        FVector2D const DragDelta = (FVector2D(Location) - LastTouchDragLocation) * CameraTouchScale;

        PanCameraHorizontal(-DragDelta.X);
        PanCameraVertical(DragDelta.Y);

        LastTouchDragLocation = FVector2D(Location);
    }
}