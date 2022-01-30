// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VESFXProjectileTrace.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class VESHOOT_API AVESFXProjectileTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	AVESFXProjectileTrace();

	void SetAttachPoint(const FName& PointName);
	void Start();

protected:
	virtual void BeginPlay() override;

	UNiagaraComponent* SpawnTraceFX();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	UNiagaraSystem* TraceFX;

private:

	UPROPERTY()
	USceneComponent* SceneComponent;

	FName ProjectileMeshSocketName = "ProjectileMeshSocket";

};
