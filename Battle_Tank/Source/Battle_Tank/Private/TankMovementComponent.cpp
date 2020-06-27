// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward,AIForwardIntention);

    IntendMoveForward(ForwardThrow);
}

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
    if (!LeftTrackToSet || !RightTrackToSet)
    {
        return;
    }
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack )
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!LeftTrack || !RightTrack )
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}