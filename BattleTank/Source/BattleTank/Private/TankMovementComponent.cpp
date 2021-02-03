// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) {
		// TODO: Report an error if having problems
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw);

	// Protect our pointers
	if (!LeftTrack || !RightTrack) {
		return;
	}

	// TODO: Clamp speed due to dual control input
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
