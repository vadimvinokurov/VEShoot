// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/VESProjectileFXTraceComponent.h"
#include "Weapon/FX/VESFXProjectileTrace.h"

UVESProjectileFXTraceComponent::UVESProjectileFXTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UVESProjectileFXTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileTraceClass);

	if (!GetOwner() || !GetWorld()) return;

	ProjectileTrace = GetWorld()->SpawnActor<AVESFXProjectileTrace>(ProjectileTraceClass);
	if (!ProjectileTrace) return;
	ProjectileTrace->SetOwner(GetOwner());
	ProjectileTrace->SetAttachPoint(ProjectileMeshSocketName);
	ProjectileTrace->Start();

	if (!ProjectileTrace || !GetOwner()->GetRootComponent()) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	ProjectileTrace->AttachToComponent(GetOwner()->GetRootComponent(), AttachmentRules, ProjectileMeshSocketName);
}

void UVESProjectileFXTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	ProjectileTrace->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ProjectileTrace->SetLifeSpan(2.0f);

	Super::EndPlay(EndPlayReason);
}
