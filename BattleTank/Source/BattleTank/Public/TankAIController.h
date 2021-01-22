// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"

#include "CoreMinimal.h"
#include "TankAIController.generated.h"


// Forward declarations
class ATank;

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

	ATank* GetControlledTank(void) const;
	ATank* GetPlayerTank(void) const;

	// Starts moving the AI tank's barrel towards the player's tank.
	//	auto AimAtPlayersTank(void)->void const;
};
