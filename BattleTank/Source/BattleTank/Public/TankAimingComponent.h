// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel;	// Holds barrel's properties and Elevate method


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	auto SetBarrelReference(UTankBarrel* BarrelToSet) -> void;
	auto SetTurretReference(UStaticMeshComponent* TurretToSet) -> void;

	auto AimAt(FVector HitLocation, float LaunchSpeed) -> void;

private:
	auto MoveBarrelTowards(FVector AimDirection) -> void;

	UTankBarrel* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;
};
