// Fill out your copyright notice in the Description page of Project Settings.

#include "VESGameModeBase.h"
#include "Player/VESBaseCharacter.h"
#include "Player/VESPlayerController.h"
#include "AIController.h"
#include "TimerManager.h"
#include "UI/VESGameHUD.h"

AVESGameModeBase::AVESGameModeBase()
{
	DefaultPawnClass = AVESBaseCharacter::StaticClass();
	PlayerControllerClass = AVESPlayerController::StaticClass();
	HUDClass = AVESGameHUD::StaticClass();
};

void AVESGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CurrentRound = 1;
	StartRound();
}

void AVESGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto VESAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(VESAIController);
	}
}

void AVESGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogTemp, Display, TEXT("Timer %i; Round %i/%i"), RoundCountdown, CurrentRound, GameData.RoundsNum);
	if (--RoundCountdown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			StartRound();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("========================= Game Over ======================"));
		}
	}
}

void AVESGameModeBase::StartRound()
{
	RoundCountdown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AVESGameModeBase::GameTimerUpdate, true, 1.0f);
}

UClass* AVESGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
