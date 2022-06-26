// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VESPlayerState.h"

void AVESPlayerState::LogInfo() const
{
	UE_LOG(LogTemp, Display, TEXT("TeamID: %i, Kills: %i, Death: %i"), TeamID, KillsNum, DeathsNum);
}
