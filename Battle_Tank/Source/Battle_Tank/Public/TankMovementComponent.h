// Copyright @2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible from driving the tank tracks
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BluePrintCallable,Category = "Input")
    void IntendMoveForward(float Throw);

	UFUNCTION(BluePrintCallable,Category = "Input")
    void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
