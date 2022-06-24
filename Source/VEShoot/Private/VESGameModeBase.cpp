// Fill out your copyright notice in the Description page of Project Settings.

#include "VESGameModeBase.h"
#include "Player/VESBaseCharacter.h"
#include "Player/VESPlayerController.h"
#include "AIController.h"
#include "UI/VESGameHUD.h"

AVESGameModeBase::AVESGameModeBase()
{
	DefaultPawnClass = AVESBaseCharacter::StaticClass();
	PlayerControllerClass = AVESPlayerController::StaticClass();
	HUDClass = AVESGameHUD::StaticClass();
};

void AVESGameModeBase::StartPlay() {
	Super::StartPlay();

	SpawnBots();
}

void AVESGameModeBase::SpawnBots() {
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto VESAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(VESAIController);
	}
}

UClass* AVESGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
