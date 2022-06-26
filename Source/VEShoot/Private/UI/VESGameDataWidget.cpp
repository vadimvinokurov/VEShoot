// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/VESGameDataWidget.h"
#include "Player/VESPlayerState.h"
#include "VESGameModeBase.h"

int32 UVESGameDataWidget::GetKillsNum() const
{
	return GetVESPlayerState() ? GetVESPlayerState()->GetKillsNum() : 0;
}

int32 UVESGameDataWidget::GetCurrentRoundNum() const
{
	return GetVESGameMode() ? GetVESGameMode()->GetCurrentRoundNum() : 0;
}

int32 UVESGameDataWidget::GetTotalRoundNum() const
{
	return GetVESGameMode() ? GetVESGameMode()->GetGameData().RoundsNum : 0;
}

int32 UVESGameDataWidget::GetRoundSecondsRemaining() const
{
	return GetVESGameMode() ? GetVESGameMode()->GetRoundSecondsRemaining() : 0;
}

AVESGameModeBase* UVESGameDataWidget::GetVESGameMode() const
{
	return GetWorld() ? Cast<AVESGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AVESPlayerState* UVESGameDataWidget::GetVESPlayerState() const
{
	return GetOwningPlayer() ? Cast<AVESPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
