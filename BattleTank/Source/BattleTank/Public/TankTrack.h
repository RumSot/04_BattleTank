// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to apply driving forces (and set a maximum) to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()


private:
	// Note: in order to make a class tick we need a constructor
	UTankTrack();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// TODO: Activate when the tracks forward key is pressed
	// Increments a throttle until it reaches its limit (currently 0 to +1)
	void Forward(void);

	// TODO: Activate when the tracks reverse key is pressed
	// Decrements a throttle until it reaches its limit (currently 0 to -1)
	void Reverse(void);

	// TODO: Pressing both keys cancels out the throttle inc/dec

	// TODO: Stop Tank both tank tracks when space is hit

	// Max force per track in 100ths of newtons
	UPROPERTY(EditDefaultsOnly)					// Note: in unreal the unit of measure is cm not m
	double TrackMaxDrivingForce = 75000000.0;	// Assume 75 tonne tank and 1G acceleration (75000 kg x 10 m/s2 x 100cm)

	float TrackThrottle = 0;
};
