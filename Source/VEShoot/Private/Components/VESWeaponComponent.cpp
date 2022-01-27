// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/VESWeaponComponent.h"
#include "Weapon/VESBaseWeapon.h"
#include "GameFramework/Character.h"

UVESWeaponComponent::UVESWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UVESWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}

void UVESWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	if (!GetWorld()) return;

	CurrentWeapon = GetWorld()->SpawnActor<AVESBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void UVESWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->Fire();
}