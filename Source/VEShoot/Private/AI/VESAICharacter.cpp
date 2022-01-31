// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VESAICharacter.h"
#include "AI/VESAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AVESAICharacter::AVESAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AVESAIController::StaticClass();

	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.f, 0.0f);
	}

}