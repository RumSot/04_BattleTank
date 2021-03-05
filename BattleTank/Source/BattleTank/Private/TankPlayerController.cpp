// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Delegates/Delegate.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay(void)
{
	Super::BeginPlay();

	// Get the controlled tanks aiming component
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// The ensure will print out an error to the log file if the argument is a nullptr
	// It will then return true if there is a pointer and false if it is a nullptr
	if (!ensure(AimingComponent)) {
		return;
	}

	FoundAimingComponent(AimingComponent);	// Broadcasts the event to Blueprint
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);	// Subscribe our local method to the tanks death event
	}
}


void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair(void)
{
	if (!GetPawn()) {	// if not possessing a tank (e.g. we have died)
		return;
	}

	// Get the controlled tanks aiming component
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	// Pointer guard, if we are possessing a tank then we should have an AimingComponent
	if (!ensure(AimingComponent)) {
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(OUT HitLocation)) 	// Has side-effect, is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}


// Get world location of a linetrace through the crosshair, true if hits landscape or tank
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector & HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		// Linetrace along the look direction, and see what we hit (up to a maximum range)
		return GetLookVectorHitlocation(LookDirection, OUT HitLocation);
	}

	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector & LookDirection) const
{
	FVector CameraWorldLocation;	// To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT CameraWorldLocation, OUT LookDirection);
}


bool ATankPlayerController::GetLookVectorHitlocation(FVector LookDirection, OUT FVector & HitLocation) const
{
	FHitResult OUT HitResult;
	auto Start = PlayerCameraManager->GetCameraLocation();
	auto End = Start + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Visibility)) 
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);

	return false;
}

void ATankPlayerController::OnTankDeath()
{
	auto Time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%f: Player tank exploded and is dead!"), Time);
}


