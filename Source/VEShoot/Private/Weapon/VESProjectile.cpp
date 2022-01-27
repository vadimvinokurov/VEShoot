// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESProjectile.h"
#include "Components/SphereComponent.h"

AVESProjectile::AVESProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);
	CollisionComponent->InitSphereRadius(5.0f);
}

void AVESProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}