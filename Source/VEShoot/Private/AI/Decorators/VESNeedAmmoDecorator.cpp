// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/VESNeedAmmoDecorator.h"
#include "AIController.h"
#include "Components/VESWeaponComponent.h"

UVESNeedAmmoDecorator::UVESNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UVESNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	if (!Controller->GetPawn()) return false;
	const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UVESWeaponComponent>();
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
