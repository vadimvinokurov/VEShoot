// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VESLauncherWeapon.h"
#include "Weapon/VESProjectile.h"

void AVESLauncherWeapon::StartFire() 
{
	MakeShot();
}

void AVESLauncherWeapon::MakeShot() 
{
	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart;
	FVector TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation());

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AVESProjectile* Projectile = GetWorld()->SpawnActorDeferred<AVESProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	// set projectile params
	DecreaseAmmo();
}
