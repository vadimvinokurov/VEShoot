// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VESLauncherWeapon.h"
#include "Weapon/VESProjectile.h"
#include "Kismet/GameplayStatics.h"

void AVESLauncherWeapon::StartFire() 
{
	MakeShot();
}

void AVESLauncherWeapon::MakeShot() 
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// set projectile params

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

}
