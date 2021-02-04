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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we are replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

//	auto Time = GetWorld()->GetTimeSeconds();
//	auto TankName = GetOwner()->GetName();
//	UE_LOG(LogTemp, Warning, TEXT("%f: %s is vectoring towards %s"), Time, *TankName, *(AIForwardIntention.ToString()));
}
