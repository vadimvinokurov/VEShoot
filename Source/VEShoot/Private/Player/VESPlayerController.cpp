// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VESPlayerController.h"
#include "Components/VESRespawnComponent.h"

AVESPlayerController::AVESPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UVESRespawnComponent>("RespawnComponent");
}