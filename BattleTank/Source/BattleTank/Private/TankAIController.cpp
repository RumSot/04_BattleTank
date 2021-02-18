// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
//#include "Engine/World.h"


void ATankAIController::BeginPlay(void)
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Get the controlled tanks aiming component
	auto ControlledTank = GetPawn();

	// Pointer guard
	if (!ensure(PlayerTank) || !ensure(ControlledTank)) {
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); 

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		AimingComponent->Fire();		// TODO: Reduce fire rate to something reasonable
	}
}
