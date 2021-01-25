// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))	//, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// The percentage of the maximum elevation speed, -1.00 is 100% downward and +1.00 is 100% upward
	void Elevate(float RelativeSpeed);

private:
	// Maximum number of degrees the barrel can move each second
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;		

	// Maximum Elevation in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40;	

	// Minimum Elevation in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;						// TODO: make minElevation -5 but only when turret rotation is between -5 and +5 degrees (i.e. facing forward)
};
