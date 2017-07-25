#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throttle)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}

void UTankMovementComponent::IntendTurnRight(float Throttle)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
}