// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VESAIWeaponComponent.h"
#include "Weapon/VESBaseWeapon.h"
void UVESAIWeaponComponent::StartFire() 
{
	if (!CanFire()) return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UVESAIWeaponComponent::NextWeapon() 
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}