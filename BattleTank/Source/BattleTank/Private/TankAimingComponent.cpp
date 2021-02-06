// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"				// If we are going to call a method then a forward declaration isn't enough
#include "TankTurret.h"

#include "Kismet/GameplayStatics.h"	


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.


//	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	if (!Barrel) {
		return;
	}

	FVector OutLaunchVelocity(0);	// Always initialise
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); 

	// Note: You can only use the defaults if you use all following defaults.
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
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


	if (bHaveAimSolution) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

//		TODO: Remove?
//		auto TankName = GetOwner()->GetName();
//		auto Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Warning, TEXT("%f: %s has an aiming soluition"), Time, *TankName);
	}
	else
	{
//		TODO: Remove?
//		auto TankName = GetOwner()->GetName();
//		auto Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Error, TEXT("%f: %s does not have an aiming soluition"), Time, *TankName);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) {
		return;
	}

	// Work out the difference between the current barrel rotation and the AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(FMath::ClampAngle(DeltaRotator.Yaw, -179, 180));	// Clamping the angle means the turret can go right around
}
