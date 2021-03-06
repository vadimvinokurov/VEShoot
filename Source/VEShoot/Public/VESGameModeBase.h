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

	void Killed(AController* KillerController, AController* VictimController);
	FGameData GetGameData() const { return GameData; }
	int32 GetCurrentRoundNum() const { return CurrentRound; }
	int32 GetRoundSecondsRemaining() const { return RoundCountdown; }

	void RespawnRequest(AController* Controller);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

private:
	void StartRespawn(AController* Controller);
	void SpawnBots();
	void GameTimerUpdate();
	void StartRound();

	void ResetPlayer();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID);
	void SetPlayerColor(AController* Controller);

	void LogPlayersInfo();

	void GameOver();

	int32 CurrentRound = 1;
	int32 RoundCountdown = 10;
	FTimerHandle GameRoundTimerHandle;
};
