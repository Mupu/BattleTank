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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector AIForwardInention = MoveVelocity.GetSafeNormal();
	
	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardInention));
	IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardInention).Z);
}
