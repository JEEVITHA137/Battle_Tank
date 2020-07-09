// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAIController.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto GetControllerTank = Cast<ATank>(GetPawn());
    auto GetPlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (ensure(GetPlayerTank))
    {

        MoveToActor(GetPlayerTank,AcceptanceRadius);

        GetControllerTank->AimAt(GetPlayerTank->GetActorLocation());

        GetControllerTank->Firing();
    }
    
}
