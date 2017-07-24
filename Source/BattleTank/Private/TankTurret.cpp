#include "TankTurret.h"
#include "Engine/World.h"

UTankTurret::UTankTurret()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}

