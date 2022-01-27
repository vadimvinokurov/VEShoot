// Fill out your copyright notice in the Description page of Project Settings.

#include "VESGameModeBase.h"
#include "Player/VESBaseCharacter.h"
#include "Player/VESPlayerController.h"
#include "UI/VESGameHUD.h"

AVESGameModeBase::AVESGameModeBase()
{
	DefaultPawnClass = AVESBaseCharacter::StaticClass();
	PlayerControllerClass = AVESPlayerController::StaticClass();
	HUDClass = AVESGameHUD::StaticClass();
};