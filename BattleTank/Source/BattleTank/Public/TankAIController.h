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

protected:
	// How close the AI tank can get to the player in cm
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0;

private:
	virtual void BeginPlay(void) override;
	virtual void Tick(float DeltaSeconds) override;


};
