// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VESAICharacter.h"
#include "AI/VESAIController.h"

AVESAICharacter::AVESAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AVESAIController::StaticClass();
}