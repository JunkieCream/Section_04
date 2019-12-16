// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "math.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector();
	auto AIForwardIntention = MoveVelocity;

	//TODO Change to GetSafeNormal when it starts to work
	auto SquareSum = (AIForwardIntention.X * AIForwardIntention.X) + (AIForwardIntention.Y * AIForwardIntention.Y) + (AIForwardIntention.Z * AIForwardIntention.Z);
	float Scale = 1/sqrt(SquareSum);
	AIForwardIntention = FVector(AIForwardIntention.X * Scale, AIForwardIntention.Y * Scale, AIForwardIntention.Z * Scale);

	float AIForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	float AITurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	
	IntendTurn(AITurnThrow);
	IntendMoveForward(AIForwardThrow);
}