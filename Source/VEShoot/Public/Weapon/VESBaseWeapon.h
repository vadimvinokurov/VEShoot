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

	virtual void StartFire();
	
	virtual void StopFire();

	bool TryToAddAmmo(int32 ClipsAmount);

	void ChangedClip();
	
	bool CanReload() const;

	bool IsClipEmpty() const;

	FWeaponUIData GetUIDate() const { return UIData; }
	
	FAmmoData GetAmmoDate() const { return CurrentAmmo; }

	FOnClipEmptySignature OnClipEmpty;

protected:
	virtual void BeginPlay() override;
	
	virtual void MakeShot();
	
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd) const;
	
	void DecreaseAmmo();
	
	bool IsAmmoEmpty() const;
	
	bool IsAmmoFull() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	APlayerController* AVESBaseWeapon::GetPlayerController() const;

	FVector GetMuzzleWorldLocation() const;

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

private:
	FAmmoData CurrentAmmo{15, 10, false};
};
