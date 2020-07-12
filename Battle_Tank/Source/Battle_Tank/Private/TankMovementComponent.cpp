// Copyright @2020

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward,AIForwardIntention);
    IntendMoveForward(ForwardThrow);

    auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if(!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}