// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/VESWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UVESWeaponFXComponent::UVESWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UVESWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
