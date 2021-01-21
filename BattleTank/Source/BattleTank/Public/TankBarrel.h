// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max upward speed
	void Elevate(float RelativeSpeed);

private:
	// Maximum number of degrees the barrel can move each second
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 1;		

	// Maximum Elevation in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40;	

	// Minimum Elevation in degrees
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;
};
