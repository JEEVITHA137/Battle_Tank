// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("Player Start Begining"));

    auto ControlledTank = GetControllerTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp,Warning,TEXT("Player not Pressing Tank"));
    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("%s"),*(ControlledTank->GetName()));
    }
    AimAtCrosshair();
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

ATank* ATankPlayerController::GetControllerTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
   
    if(!GetControllerTank()) { return;}
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
    
    }
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation,ViewPortSizeY * CrossHairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("ScreenLocation:%s"), *ScreenLocation.ToString());

    return true;
}