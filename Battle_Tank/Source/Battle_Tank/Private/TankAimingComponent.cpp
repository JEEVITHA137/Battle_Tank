// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel=BarrelToSet;
	Turret=TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
    if (!ensure(Barrel)){ return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
													// TODO report bug
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Barrel) || !ensure(Turret)){ return; }
	UE_LOG(LogTemp,Warning,TEXT("Im Here"));
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
    
	Barrel->Elevate(DeltaRotator.Pitch);

	Turret->Rotate(DeltaRotator.Yaw);
}

void  UTankAimingComponent::Firing()
{
	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}
	bool IsReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReload)
	{

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}