// Copyright @2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

    private:

		void AimAtCrosshair();

		bool GetSightRayHitLocation(FVector& OutHitLocation) const;
		bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
		bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const;

		UPROPERTY(EditDefaultsOnly) 
		float CrossHairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.3333f;

		UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	protected:
		UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControllerTank() const;

		UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
};
