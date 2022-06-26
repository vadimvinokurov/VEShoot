// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VESHOOT_API UVESRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVESRespawnComponent();

	void Respawn(int32 RespawnTime);

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle RespawnTimerHandle;
	int32 TimerCountdown = 0;
	void RespawnTimerUpdate();
};
