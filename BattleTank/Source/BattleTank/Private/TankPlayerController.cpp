// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

#include "Engine/World.h"


void ATankPlayerController::BeginPlay(void)
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerContoller isn't possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has possessed %s"), *(ControlledTank->GetName()));
	}

	// Whenever PlayersTank is used place a guard against nullptr at the top of the function
	// if (!PlayerTank) return;

}


void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

auto ATankPlayerController::GetControlledTank(void) -> ATank* const
{
	auto PlayerPawn = GetPawn();

	if (!PlayerPawn) {
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);		// In the event of a nullptr or an invalid pointer this cast would fail. So we could remove the nullptr guard above (however I choose to be specific for clarity).
}

#define OUT

auto ATankPlayerController::AimTowardsCrosshair(void) -> void
{
	// Pointer guard
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(OUT HitLocation)) 	// Has side-effect, is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}


// Get world location of a linetrace through the crosshair, true if hits landscape or tank
auto ATankPlayerController::GetSightRayHitLocation(OUT FVector &HitLocation) -> bool const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Linetrace along the look direction, and see what we hit (up to a maximum range)
		GetLookVectorHitlocation(LookDirection, OUT HitLocation);
	}

	return true;
}

auto ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector & LookDirection) -> bool const
{
	FVector CameraWorldLocation;	// To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT CameraWorldLocation, OUT LookDirection);
}

auto ATankPlayerController::GetLookVectorHitlocation(FVector LookDirection, OUT FVector & HitLocation) -> bool const
{
	FHitResult OUT HitResult;
	auto Start = PlayerCameraManager->GetCameraLocation();
	auto End = Start + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.ImpactPoint;
//		UE_LOG(LogTemp, Warning, TEXT("HitImpactPoint: %s"), *HitResult.Location.ToString());
//		UE_LOG(LogTemp, Warning, TEXT("HitImpactPoint: %s"), *HitResult.ImpactPoint.ToString());
		return true;
	}

//	HitLocation = FVector(0.0);
	return false;
}


