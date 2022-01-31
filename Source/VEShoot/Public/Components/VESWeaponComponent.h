// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESCoreTypes.h"

#include "VESWeaponComponent.generated.h"

class AVESBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VESHOOT_API UVESWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVESWeaponComponent();

	virtual void StartFire();

	void StopFire();

	virtual void NextWeapon();

	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	bool GetAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<AVESBaseWeapon> WeaponType, int32 ClipsAmount);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	bool CanEquip() const;

	bool CanFire() const;

	void EquipWeapon(int32 WeaponIndex);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	AVESBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AVESBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

private:
	void InitAnimation();

	void SpawnWeapons();

	void AttachWeaponToSocket(AVESBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* EquipAnimMontage);

	void ChangedClip();

	bool CanReload() const;

	void OnClipEmpty(AVESBaseWeapon* AmmoEmptyWeapon);

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;

	bool ReloadAnimInProgress = false;
};
