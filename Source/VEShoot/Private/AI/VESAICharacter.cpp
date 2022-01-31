// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VESAICharacter.h"
#include "AI/VESAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/VESAIWeaponComponent.h"
#include "BrainComponent.h"

AVESAICharacter::AVESAICharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UVESAIWeaponComponent>("WeaponComponent"))
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

void AVESAICharacter::OnDeath() 
{
	Super::OnDeath();
	const auto VESController = Cast<AAIController>(Controller);
	if (VESController && VESController->BrainComponent)
	{
		VESController->BrainComponent->Cleanup();
	}
}
