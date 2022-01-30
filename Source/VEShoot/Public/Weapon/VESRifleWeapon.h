// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VESBaseWeapon.h"
#include "VESRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class VESHOOT_API AVESRifleWeapon : public AVESBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float TimeBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 10;

	virtual void MakeShot() override;
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;
};
