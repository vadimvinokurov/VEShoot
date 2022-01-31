// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VESAIController.h"
#include "AI/VESAICharacter.h"

void AVESAIController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);

	const auto VESCharacter = Cast<AVESAICharacter>(InPawn);

	if (VESCharacter)
	{
		RunBehaviorTree(VESCharacter->BehaviorTreeAsset);
	}
}