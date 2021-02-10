// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  
	// We have turned this off to improve performance as Tank doesn't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	// Needed for Blueprint BeginPlay to run
}


void ATank::Fire()
{
}
/*if (!ensure(Barrel)) {
		return;
	}

	// Note: FPlatformTime::Seconds() is problematic as it is the system time and hence continues when the game is paused.
	bool bIsReloaded = ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds);

	if (bIsReloaded) {
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(5000); // LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}*/

