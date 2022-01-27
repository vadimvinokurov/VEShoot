// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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
