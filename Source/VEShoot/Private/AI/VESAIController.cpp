// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/VESAIController.h"
#include "AI/VESAICharacter.h"
#include "Components/VESAIPerceptionComponent.h"
#include "Components/VESRespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AVESAIController::AVESAIController()
{
	VESAIPerceptionComponent = CreateDefaultSubobject<UVESAIPerceptionComponent>("VESAIPerceptionComponent");
	SetPerceptionComponent(*VESAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UVESRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void AVESAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto VESCharacter = Cast<AVESAICharacter>(InPawn);

	if (VESCharacter)
	{
		RunBehaviorTree(VESCharacter->BehaviorTreeAsset);
	}
}

void AVESAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = VESAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}

AActor* AVESAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
