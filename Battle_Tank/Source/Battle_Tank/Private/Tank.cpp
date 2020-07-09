// Copyright @2020

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector OutHitLocation)
{
	if(!ensure(TankAimingComponent)){ return; }
	TankAimingComponent->AimAt(OutHitLocation,LaunchSpeed);
}

void ATank::Firing()
{
	if (!ensure(Barrel))
	{
		return;
	}
	bool IsReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReload)
	{

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}