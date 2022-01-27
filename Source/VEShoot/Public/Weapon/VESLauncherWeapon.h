// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VESBaseWeapon.h"
#include "VESLauncherWeapon.generated.h"

/**
 *
 */
class AVESProjectile;

UCLASS()
class VESHOOT_API AVESLauncherWeapon : public AVESBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AVESProjectile> ProjectileClass;
	virtual void MakeShot() override;
};
