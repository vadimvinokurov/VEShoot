// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/VESCharacterMovementComponent.h"
#include "Player/VESBaseCharacter.h"

float UVESCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AVESBaseCharacter* Player = Cast<AVESBaseCharacter>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}