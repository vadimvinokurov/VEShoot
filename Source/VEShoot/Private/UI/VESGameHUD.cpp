// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/VESGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AVESGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AVESGameHUD::BeginPlay() 
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}