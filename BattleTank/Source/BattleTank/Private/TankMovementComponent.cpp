// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	// Protect our pointers
	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// Protect our pointers
	if (!LeftTrack || !RightTrack) {
		return;
	}

	// TODO: Clamp speed due to dual control input
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// Protect our pointers
	if (!LeftTrack || !RightTrack) {
		return;
	}

	// TODO: Clamp speed due to dual control input
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
