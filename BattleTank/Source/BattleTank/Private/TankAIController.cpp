// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

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

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("AIContoller couldn't find the player's tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has found players tank: %s"), *(PlayerTank->GetName()));
	}

	// Whenever PlayersTank is used place a guard against nullptr at the top of the function
	// if (!PlayerTank) return;

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Pointer guard
	if (GetPlayerTank()) {
		// TODO: Move towards the player

		AimAtPlayersTank();

		// TODO: Fire if ready
	}
}

auto ATankAIController::GetControlledTank(void)->ATank* const
{
	auto AIPawn = GetPawn();

	if (!AIPawn) {
		return nullptr;
	}

	return Cast<ATank>(AIPawn);
}

auto ATankAIController::GetPlayerTank(void) -> ATank * const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) {
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);
}

auto ATankAIController::AimAtPlayersTank(void) -> void const
{
	// Pointer guard
	if (!GetControlledTank()) {
		return;
	}

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
