// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/VESWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
UVESWeaponFXComponent::UVESWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UVESWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
