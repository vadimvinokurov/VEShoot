// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));

	CurrentAmmo = DefaultAmmo;
}

void AVESBaseWeapon::MakeShot() {}

void AVESBaseWeapon::StartFire() {}

void AVESBaseWeapon::StopFire() {}

APlayerController* AVESBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool AVESBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector AVESBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AVESBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void AVESBaseWeapon::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd) const
{
	if (!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AVESBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty"));
		return;
	}
	--CurrentAmmo.Bullets;

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool AVESBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

bool AVESBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}



void AVESBaseWeapon::ChangedClip()
{
	
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	UE_LOG(LogBaseWeapon, Display, TEXT("------- Changed Clip ----------"));
}

void AVESBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool AVESBaseWeapon::CanReload() const 
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}