// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VESAIPerceptionComponent.h"
#include "AIController.h"
#include "VESUtils.h"
#include "Components/VESHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UVESAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = PercieveActor->FindComponentByClass<UVESHealthComponent>();
		if (HealthComponent && !HealthComponent->IsDead())	 // TODO: check if enemies or not
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}