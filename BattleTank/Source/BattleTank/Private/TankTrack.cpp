// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	// The tracks x-axis is aligned with the tanks direction, 
	// hence the forward vector gives us the direction of movement (positive for forward, negative for reverse)
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	// The tracks socket location is where we want to apply the force
	auto ForceLocation = GetComponentLocation();

	// https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UStaticMeshComponent/index.html
	// First we get the tracks root component, then we try to add force at the location.
	// This will not be possible for the USceneComponent, so we cast down until AddForceAtLocation() becomes available.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::Forward(void)
{
}

void UTankTrack::Reverse(void)
{
}
