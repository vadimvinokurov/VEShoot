// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/VESHealthPickup.h"
#include "Components/VESHealthComponent.h"
#include "VESUtils.h"

bool AVESHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = VESUtils::GetVESPlayerComponent<UVESHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
