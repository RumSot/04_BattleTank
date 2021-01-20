// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreedPerSecond) {
	// Move the barrel the right amount this frame
	// Given a max elevation speed, max rotation speed, and the frame rate.

	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called a speed %f"), DegreedPerSecond);
}