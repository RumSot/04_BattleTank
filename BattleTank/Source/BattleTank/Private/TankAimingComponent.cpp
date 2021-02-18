// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"				// If we are going to call a method then a forward declaration isn't enough
#include "TankTurret.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"	


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.


//	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Note: FPlatformTime::Seconds() is problematic as it is the system time and hence continues when the game is paused.
	if (RoundsLeft <= 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}	
	else if (((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming) {
		if (!ensure(Barrel)) {
			return;
		}
		if (!ensure(ProjectileBlueprint)) {
			return;
		}

		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		RoundsLeft--;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
	if (!ensure(Barrel)) {
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


	AimDirection = OutLaunchVelocity.GetSafeNormal();

	if (bHaveAimSolution) 
	{
		MoveBarrelTowardsAimDirection();

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

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}


void UTankAimingComponent::MoveBarrelTowardsAimDirection()
{
	// The ensure will print out an error to the log file if the argument is a nullptr
	// It will then return true if there is a pointer and false if it is a nullptr
	if (!ensure(Barrel) || !ensure(Turret)) {
		return;
	}

	// Work out the difference between the current barrel rotation and the AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	auto ShortestAngle = (DeltaRotator.Yaw <= 180) ? DeltaRotator.Yaw : -DeltaRotator.Yaw;
	Turret->Rotate(ShortestAngle);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) {
		return false;
	}

	auto BarrelDirection = Barrel->GetForwardVector();	// better for documentation than putting it all on one line

	return !(BarrelDirection.Equals(AimDirection, 0.1f));
}
