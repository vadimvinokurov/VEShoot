// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/VESBaseCharacter.h"
#include "VESAICharacter.generated.h"

/**
 *
 */
class UBehaviorTree;

UCLASS()
class VESHOOT_API AVESAICharacter : public AVESBaseCharacter
{
	GENERATED_BODY()

public:
	AVESAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
