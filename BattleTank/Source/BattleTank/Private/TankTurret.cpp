// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max rotation speed and the frame rate.

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}