// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


auto UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet) -> void
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

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
	// EndLocation is the HitLocation;
	// TossSpeed is the LaunchSpeed
	// bHighArc is false as we want the quickest route to target

	if	( UGameplayStatics::SuggestProjectileVelocity
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
			)
		) 
	{
		auto TankName = GetOwner()->GetName();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
	}
}
