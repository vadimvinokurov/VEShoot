// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/Services/VEChangeWeaponService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/VESAIPerceptionComponent.h"
#include "Components/VESWeaponComponent.h"

UVEChangeWeaponService::UVEChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UVEChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UVESWeaponComponent>();
		
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}