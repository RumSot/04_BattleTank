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

	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);

public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track in 100ths of newtons
	UPROPERTY(EditDefaultsOnly)					// Note: in unreal the unit of measure is cm not m
	double TrackMaxDrivingForce = 400000.0;	// Assume 40 tonne tank and 1G acceleration (40000 kg x 10 m/s)
};

