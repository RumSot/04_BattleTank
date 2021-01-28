// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: clamp the throttle
	Throttle = FMath::Clamp(Throttle, -1.0f, +1.0f);

	//auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
}

void UTankTrack::Forward(float Speed)
{
}

void UTankTrack::Reverse(float Speed)
{
}
