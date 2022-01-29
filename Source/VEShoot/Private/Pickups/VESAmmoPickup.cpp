// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/VESAmmoPickup.h"
#include "Components/VESHealthComponent.h"
#include "Components/VESWeaponComponent.h"
#include "VESUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AVESAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = VESUtils::GetVESPlayerComponent<UVESHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = VESUtils::GetVESPlayerComponent<UVESWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}