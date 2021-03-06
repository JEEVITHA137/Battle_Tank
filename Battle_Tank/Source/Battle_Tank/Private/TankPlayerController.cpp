// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
    if(!GetPawn()){ return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent))
    {
        return;
    }

    FVector OutHitLocation;
    bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
    if (bGotHitLocation)
    {
        AimingComponent->AimAt(OutHitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation,ViewPortSizeY * CrossHairYLocation);

    FVector LookDirection;
    if(GetLookDirection(ScreenLocation,LookDirection))
    {
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const
{
    FHitResult HitResult;
    auto StartingPoint = PlayerCameraManager->GetCameraLocation();
    auto EndPoint = StartingPoint + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartingPoint,
            EndPoint,
            ECollisionChannel::ECC_Camera))
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    OutHitLocation = FVector(0);
    return false;
}