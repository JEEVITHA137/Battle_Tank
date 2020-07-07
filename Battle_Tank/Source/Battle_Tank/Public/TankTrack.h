
//Copyright @2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force,and to apply the forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


 public:
     UFUNCTION(BluePrintCallable,Category = "Input")
     void SetThrottle(float Throttle);

	 UPROPERTY(EditDefaultsOnly)
	 float TrackMaxDrivingForce = 40000000;
	
};
