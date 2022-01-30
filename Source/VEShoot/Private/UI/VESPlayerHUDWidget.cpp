// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/VESPlayerHUDWidget.h"
#include "Components/VESHealthComponent.h"
#include "Components/VESWeaponComponent.h"
#include "VESUtils.h"

float UVESPlayerHUDWidget::GetHealthPrecent() const
{
	const auto HealthComponent = VESUtils::GetVESPlayerComponent<UVESHealthComponent>(GetOwningPlayerPawn());

	if (!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthProcent();
}

bool UVESPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = VESUtils::GetVESPlayerComponent<UVESWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UVESPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = VESUtils::GetVESPlayerComponent<UVESWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetAmmoData(AmmoData);
}

bool UVESPlayerHUDWidget::IsPlayerAliver() const
{
	const auto HealthComponent = VESUtils::GetVESPlayerComponent<UVESHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UVESPlayerHUDWidget::IsPlayerSpecating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UVESPlayerHUDWidget::Initialize()
{
	const auto HealthComponent = VESUtils::GetVESPlayerComponent<UVESHealthComponent>(GetOwningPlayerPawn());
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UVESPlayerHUDWidget::OnHealthChange);
	}
	return Super::Initialize();
}

void UVESPlayerHUDWidget::OnHealthChange(float Health, float DeltaHealth)
{
	if (DeltaHealth < 0)
	{
		OnTakeDamage();
	}
}
