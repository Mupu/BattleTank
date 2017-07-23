// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;
	UE_LOG(LogTemp, Warning, TEXT("%f   :   %f"), RawNewRotation, RelativeSpeed);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

