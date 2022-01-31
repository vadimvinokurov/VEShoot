// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "VESHealthPercentDecorator.generated.h"

/**
 *
 */
UCLASS()
class VESHOOT_API UVESHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UVESHealthPercentDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;
};
