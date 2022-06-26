// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VESPlayerState.generated.h"

/**
 *
 */
UCLASS()
class VESHOOT_API AVESPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamID(int32 ID) { TeamID = ID; }
	int32 GetTeamID() const { return TeamID; }
	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	const FLinearColor& GetTeamColor() const { return TeamColor; }

	void AddKill() { ++KillsNum; }
	int32 GetKillsNum() { return KillsNum; }

	void AddDeath() { ++DeathsNum; }
	int32 GetDeathsNum() { return DeathsNum; }

	void LogInfo() const;

private:
	int32 TeamID;
	FLinearColor TeamColor;
	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
