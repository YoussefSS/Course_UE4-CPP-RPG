// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check to make sure everything is still valid and that we're allowed to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get and clear the vector from Collider
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.f) * DeltaTime * 150.f; // Will consume the AddInputVector we have in Collider.cpp

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bump into something, slide along the side of it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}