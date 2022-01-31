// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "VESNeedAmmoDecorator.generated.h"

/**
 * 
 */
class AVESBaseWeapon;
UCLASS()
class VESHOOT_API UVESNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UVESNeedAmmoDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AVESBaseWeapon> WeaponType;
};
