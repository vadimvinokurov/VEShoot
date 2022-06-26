// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VESPlayerController.generated.h"

class UVESRespawnComponent;
/**
 *
 */
UCLASS()
class VESHOOT_API AVESPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVESPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Components")
	UVESRespawnComponent* RespawnComponent;

	virtual void OnPossess(APawn* aPawn) override;
};
