// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track on ground"));
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto Velocity = GetComponentVelocity();
	auto RightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(Velocity, RightVector);	// the order of a dot product doesn't matter

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -((SlippageSpeed / DeltaTime) * RightVector);

	// Calulate and appy sideways force (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());		// this takes us from a UTankTrack to a USceneComponent
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;		// there are two tracks hence we divide by 2
	TankRoot->AddForce(CorrectionForce);
}


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

