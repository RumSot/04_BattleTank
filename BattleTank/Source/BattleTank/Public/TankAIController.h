// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "CoreMinimal.h"
#include "TankAIController.generated.h"


// Forward declarations

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay(void) override;
	virtual void Tick(float DeltaSeconds) override;

	// How close the AI tank can get to the player
	float AcceptanceRadius = 3000; // TODO: check radius is in cm
};
