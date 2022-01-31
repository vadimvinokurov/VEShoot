// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VESAIController.generated.h"

class UVESAIPerceptionComponent;

UCLASS()
class VESHOOT_API AVESAIController : public AAIController
{
	GENERATED_BODY()

public:
	AVESAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UVESAIPerceptionComponent* VESAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	FName FocusOnKeyName = "EnemyActor";

private:
	AActor* GetFocusOnActor() const;
};
