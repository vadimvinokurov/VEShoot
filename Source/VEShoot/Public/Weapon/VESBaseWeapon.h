// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VESCoreTypes.h"

#include "VESBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class VESHOOT_API AVESBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AVESBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	void ChangedClip();
	bool CanReload() const;

	FWeaponUIData GetUIDate() const { return UIData; }
	FAmmoData GetAmmoDate() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);

	bool IsClipEmpty() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	APlayerController* AVESBaseWeapon::GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd) const;

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;
	void LogAmmo();

private:
	FAmmoData CurrentAmmo{15, 10, false};
};
