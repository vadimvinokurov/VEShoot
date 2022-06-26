// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VESPlayerController.h"
#include "Components/VESRespawnComponent.h"

AVESPlayerController::AVESPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UVESRespawnComponent>("RespawnComponent");
}

void AVESPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
};