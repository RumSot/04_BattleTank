// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"		// Always the last include


// Forward declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player to aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimComRef);

private:
	virtual void BeginPlay(void) override;
	virtual void Tick(float DeltaSeconds) override;

	// Starts moving the tank's barrel towards the point where the croshair intersects with the world.
	void AimTowardsCrosshair(void);

	// Returns true if it hits anything
	bool GetSightRayHitLocation(OUT FVector &HitLocation) const;

	// De-project the screen position of the crosshair to a world direction
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector &LookDirection) const;
	bool GetLookVectorHitlocation(FVector LookDirection, OUT FVector &HitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairXLocation = 0.5f;		// distance from the top left

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LineTraceRange = 1000000;	// 10km
};
