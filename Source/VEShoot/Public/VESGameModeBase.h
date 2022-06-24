// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VESCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "VESGameModeBase.generated.h"

/**
 *
 */

class AAIController;
UCLASS()
class VESHOOT_API AVESGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVESGameModeBase();
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

private:
	void SpawnBots();
	void GameTimerUpdate();
	void StartRound();

	int32 CurrentRound = 1;
	int32 RoundCountdown = 10;
	FTimerHandle GameRoundTimerHandle;

};
