// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO: Tell controlled tank to aim at this point
	}
}


// Get world location of a linetrace through the crosshair, true if hits landscape or tank
auto ATankPlayerController::GetSightRayHitLocation(OUT FVector &HitLocation) -> bool const
{

	// TODO: Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// TODO: De-project the screen position of the crosshair to a world position
	// TODO: Linetrace along the look direction, and see what we hit (up to a maximum range)
	
	return true;
}


