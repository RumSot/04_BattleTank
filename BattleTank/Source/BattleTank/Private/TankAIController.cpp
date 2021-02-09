// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay(void)
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	// Pointer guard
	if (ensure(PlayerTank)) {
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); 

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();		// TODO: Reduce fire rate to something reasonable
	}
}
