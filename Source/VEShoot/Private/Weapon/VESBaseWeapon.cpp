// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
AVESBaseWeapon::AVESBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}



void AVESBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AVESBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("FIRE!!!!!!!"));
}
