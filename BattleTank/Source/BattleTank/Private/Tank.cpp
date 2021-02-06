// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  
	// We have turned this off to improve performance as Tank doesn't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: ATank::AimAt(): TankAimingComponent is a nullptr"), Time);

		return;
	}

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	// Note: FPlatformTime::Seconds() is problematic as it is the system time and hence continues when the game is paused.
	bool bIsReloaded = ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds);

	if (Barrel && bIsReloaded) {
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

