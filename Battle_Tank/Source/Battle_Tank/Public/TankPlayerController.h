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
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

    private:
		ATank *GetControllerTank() const;
		void AimAtCrosshair();

		bool GetSightRayHitLocation(FVector& OutHitLocation) const;
		bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

		UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

		UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333f;
		
};
