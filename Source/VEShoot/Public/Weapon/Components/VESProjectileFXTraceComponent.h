// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESProjectileFXTraceComponent.generated.h"

class AVESFXProjectileTrace;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VESHOOT_API UVESProjectileFXTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVESProjectileFXTraceComponent();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	TSubclassOf<AVESFXProjectileTrace> ProjectileTraceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	FName ProjectileMeshSocketName = "ProjectileMeshSocket";

private:
	UPROPERTY()
	AVESFXProjectileTrace* ProjectileTrace;
	
};
