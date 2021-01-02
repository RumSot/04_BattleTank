// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

auto ATankPlayerController::GetControlledTank(void) -> ATank* const {
	return Cast<ATank>(GetPawn());
}

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


	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}
