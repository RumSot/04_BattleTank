// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay(void) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	auto GetControlledTank(void)->ATank* const;
	auto GetPlayerTank(void)->ATank* const;

	// Starts moving the AI tank's barrel towards the player's tank.
	auto AimAtPlayersTank(void)->void const;
};
