// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Delegates/Delegate.h"
//#include "Engine/World.h"


void ATankAIController::BeginPlay(void)
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);	// Subscribe our local method to the tanks death event
	}
}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) {
		return;
	}


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

void ATankAIController::OnTankDeath()
{
	auto Time = GetWorld()->GetTimeSeconds();

	if (!GetPawn()) {
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();

	UE_LOG(LogTemp, Warning, TEXT("%f: AI tank exploded and is dead!"), Time);
}
