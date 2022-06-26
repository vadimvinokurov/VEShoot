// Fill out your copyright notice in the Description page of Project Settings.

#include "VESGameModeBase.h"
#include "Player/VESBaseCharacter.h"
#include "Player/VESPlayerController.h"
#include "Player/VESPlayerState.h"
#include "AIController.h"
#include "TimerManager.h"
#include "UI/VESGameHUD.h"
#include "VESUtils.h"
#include "Components/VESRespawnComponent.h"

AVESGameModeBase::AVESGameModeBase()
{
	DefaultPawnClass = AVESBaseCharacter::StaticClass();
	PlayerControllerClass = AVESPlayerController::StaticClass();
	HUDClass = AVESGameHUD::StaticClass();
	PlayerStateClass = AVESPlayerState::StaticClass();
};

void AVESGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamInfo();
	CurrentRound = 1;
	StartRound();
}

void AVESGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AVESPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AVESPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	StartRespawn(VictimController);
}

void AVESGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void AVESGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = VESUtils::GetVESPlayerComponent<UVESRespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.ResoawnTime);
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
			ResetPlayer();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("========================= Game Over ======================"));
			LogPlayersInfo();
		}
	}
}

void AVESGameModeBase::StartRound()
{
	const auto RestartAvailable = RoundCountdown > GameData.MinRoundTimeForRespawn + GameData.ResoawnTime;
	if (RestartAvailable) return;
	RoundCountdown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AVESGameModeBase::GameTimerUpdate, true, 1.0f);
}

void AVESGameModeBase::ResetPlayer()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; It++)
	{
		ResetOnePlayer(It->Get());
	}
}

void AVESGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AVESGameModeBase::CreateTeamInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 0;
	for (auto It = GetWorld()->GetControllerIterator(); It; It++)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AVESPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		TeamID = (TeamID + 1) % 2;
	}
}

FLinearColor AVESGameModeBase::DetermineColorByTeamID(int32 TeamID)
{
	if (TeamID < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID];
	}
	else
	{
		return GameData.DefaultTeamColor;
	}
}

void AVESGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<AVESBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AVESPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AVESGameModeBase::LogPlayersInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 0;
	for (auto It = GetWorld()->GetControllerIterator(); It; It++)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AVESPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
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
