// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VESGameDataWidget.generated.h"

class AVESGameModeBase;
class AVESPlayerState;
/**
 *
 */
UCLASS()
class VESHOOT_API UVESGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BLueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BLueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BLueprintCallable, Category = "UI")
	int32 GetTotalRoundNum() const;

	UFUNCTION(BLueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	AVESGameModeBase* GetVESGameMode() const;
	AVESPlayerState* GetVESPlayerState() const;
};
