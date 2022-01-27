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
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<AVESBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}

void UVESWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->Fire();
}