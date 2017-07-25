#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Throttle);
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}