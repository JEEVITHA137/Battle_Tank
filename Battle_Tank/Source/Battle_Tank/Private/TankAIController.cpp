// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) { return; }

    MoveToActor(PlayerTank,AcceptanceRadius);

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Firing();
    }
}

void ATankAIController::SetPawn(APawn *InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
	{
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank))
        {
            return;
        }

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
    }
}

void ATankAIController::OnPossedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Received!"))
}