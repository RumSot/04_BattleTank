// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto CurrentThrottle = FMath::Clamp<float>(Throttle, -1, +1);
	DriveTrack(CurrentThrottle);
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Result;

	TArray<USceneComponent*> Children;
	USceneComponent::GetChildrenComponents(true, OUT Children);

	for (auto Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);	// Note: Cast will return a nullptr if it fails
		if (!SpawnPointChild) continue;

		auto SpawnedActor = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedActor);	// Note: Cast will return a nullptr if it fails
		if (!SprungWheel) continue;

		Result.Add(SprungWheel);
	}

	return Result;
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (auto Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}


