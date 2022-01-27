// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESWeaponComponent.generated.h"


class AVESBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VESHOOT_API UVESWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVESWeaponComponent();

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AVESBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AVESBaseWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
};
