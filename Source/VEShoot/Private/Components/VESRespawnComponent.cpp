// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/VESRespawnComponent.h"
#include "VESGameModeBase.h"

UVESRespawnComponent::UVESRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UVESRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;
	TimerCountdown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UVESRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void UVESRespawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UVESRespawnComponent::RespawnTimerUpdate()
{
	if (--TimerCountdown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AVESGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
