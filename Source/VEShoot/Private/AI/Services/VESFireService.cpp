// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/VESFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/VESAIPerceptionComponent.h"
#include "Components/VESWeaponComponent.h"

UVESFireService::UVESFireService() 
{
	NodeName = "Fire";
}

void UVESFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UVESWeaponComponent>();

		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}