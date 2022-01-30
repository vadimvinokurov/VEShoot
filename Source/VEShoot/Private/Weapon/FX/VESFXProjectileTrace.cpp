// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FX/VESFXProjectileTrace.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AVESFXProjectileTrace::AVESFXProjectileTrace()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void AVESFXProjectileTrace::SetAttachPoint(const FName& PointName) 
{
	ProjectileMeshSocketName = PointName;
}

void AVESFXProjectileTrace::BeginPlay()
{
	Super::BeginPlay();
}

void AVESFXProjectileTrace::Start() 
{
	auto FXComponent = SpawnTraceFX();
}

UNiagaraComponent* AVESFXProjectileTrace::SpawnTraceFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(TraceFX,  //
		SceneComponent,											   //
		ProjectileMeshSocketName,								   //
		FVector::ZeroVector,									   //
		FRotator::ZeroRotator,									   //
		EAttachLocation::SnapToTarget,							   //
		true);
}

