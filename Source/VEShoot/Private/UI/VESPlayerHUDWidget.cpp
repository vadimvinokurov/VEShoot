// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/VESPlayerHUDWidget.h"
#include "Components/VESHealthComponent.h"
#include "Components/VESWeaponComponent.h"

float UVESPlayerHUDWidget::GetHealthPrecent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;
	const auto Component = Player->GetComponentByClass(UVESHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UVESHealthComponent>(Component);

	if (!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthProcent();
}

bool UVESPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;
	const auto Component = Player->GetComponentByClass(UVESWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UVESWeaponComponent>(Component);
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}
