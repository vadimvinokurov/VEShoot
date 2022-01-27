// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESWeaponComponent.generated.h"

class AVESBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VESHOOT_API UVESWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVESWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<AVESBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	UPROPERTY()
	AVESBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AVESBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(AVESBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* EquipAnimMontage);
	void InitAnimation();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	bool CanEquip() const;
	bool CanFire() const;
};
