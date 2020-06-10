// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp,Warning,TEXT("Player Start Begining"));

    auto GetPlayer = GetPlayerTank();
    if(!GetPlayer)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not Getting Player Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank is %s"), *(GetPlayer->GetName()));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(GetPlayerTank())
    {
        GetControllerTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
    
}

ATank* ATankAIController::GetControllerTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}