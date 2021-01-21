// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"		// Always the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay(void) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	auto GetControlledTank(void)->ATank* const;

	// Starts moving the tank's barrel towards the point where the croshair intersects with the world.
	auto AimTowardsCrosshair(void)->void;

	// Returns true if it hits anything
	auto GetSightRayHitLocation(OUT FVector &HitLocation)->bool const;

	// De-project the screen position of the crosshair to a world direction
	auto GetLookDirection(FVector2D ScreenLocation, OUT FVector &LookDirection) -> bool const;

	auto GetLookVectorHitlocation(FVector LookDirection, OUT FVector &HitLocation) -> bool const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;		// distance from the top left

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 5.0f * 100 * 1000;	// 5km = 5cm * 100 to give meters * 1000 to give km
};
