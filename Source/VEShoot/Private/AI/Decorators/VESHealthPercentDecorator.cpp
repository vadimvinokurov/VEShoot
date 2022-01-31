// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/VESHealthPercentDecorator.h"
#include "AIController.h"
#include "Components/VESHealthComponent.h"

UVESHealthPercentDecorator::UVESHealthPercentDecorator() 
{
	NodeName = "Health Percent";
}

bool UVESHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	if (!Controller->GetPawn()) return false;
	const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<UVESHealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthProcent() <= HealthPercent;
}
