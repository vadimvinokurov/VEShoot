// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/VESWeaponFXComponent.h"

AVESRifleWeapon::AVESRifleWeapon() 
{
	WeaponFXComponent = CreateDefaultSubobject<UVESWeaponFXComponent>("WeaponFXComponent");
}

void AVESRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AVESRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void AVESRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void AVESRifleWeapon::BeginPlay() 
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void AVESRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsClipEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;

	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	DecreaseAmmo();
}

bool AVESRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void AVESRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}
