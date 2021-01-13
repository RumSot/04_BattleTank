// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

auto ATankAIController::GetControlledTank(void)->ATank* const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay(void)
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AIContoller isn't possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has possessed %s"), *(ControlledTank->GetName()));
	}

	// Whenever PlayersTank is used place a guard against nullptr at the top of the function
	// if (!PlayerTank) return;

}
