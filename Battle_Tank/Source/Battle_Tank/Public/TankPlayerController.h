// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	    ATank* GetControllerTank() const;

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		void AimAtCrosshair();

        UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

        UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333f;

    private:
		bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	
};
