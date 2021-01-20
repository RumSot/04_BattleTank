// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"				// If we are going to call a method then a forward declaration isn't enough
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


auto UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) -> void
{
	Barrel = BarrelToSet;
}

auto UTankAimingComponent::SetTurretReference(UStaticMeshComponent * TurretToSet) -> void
{
	Turret = TurretToSet;
}


auto UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) -> void
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	if (!Barrel) {
		return;
	}

	FVector OutLaunchVelocity(0);	// Always initialise
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	auto bHaveAimingSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,											// bool bHighArc defaults to false
		0.0f,											// CollisionRadius defaults to 0.0f
		0.0f,											// OverrideGravityZ defaults to 0.0f (i.e. no effect)
		ESuggestProjVelocityTraceOption::DoNotTrace		// ESuggestProjVelocityTraceOption defaults to ESuggestProjVelocityTraceOption::TraceFullPath
	);

	if (bHaveAimingSolution) {
		auto TankName = GetOwner()->GetName();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
	}
	// if no solution found then do nothing.
}

auto UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) -> void
{
	// calculate the degrees that the turret needs to be rotated from its current position to the target direction
	// calculate the degrees that the barrel needs to be raised or lowered
	// move the barrel towards the target at a set speed

	// Work out how far the turret needs rotating and the barrel needs elevating
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(5);		// TODO: remove magic number
}

