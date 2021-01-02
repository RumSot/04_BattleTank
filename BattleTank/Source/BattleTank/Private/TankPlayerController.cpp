// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

auto ATankPlayerController::GetControlledTank(void) -> ATank* const {
	return Cast<ATank>(GetPawn());
}