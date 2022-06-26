// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VESBaseWeapon.h"
#include "VESRifleWeapon.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class UVESWeaponFXComponent;
 
UCLASS()
class VESHOOT_API AVESRifleWeapon : public AVESBaseWeapon
{
	GENERATED_BODY()
public:
	AVESRifleWeapon();

	virtual void StartFire() override;
	
	virtual void StopFire() override;

protected:
	virtual void BeginPlay() override;

	virtual void MakeShot() override;
	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FX")
	UVESWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
	FString TraceTargetName = "TraceTarget";

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	void InitMuzzleFX();

	void SetMuzzleFXVisibility(bool Visible);

	void SpawnTaceFX(const FVector& TraceStart, const FVector& TraceEnd); 

	AController* GetController() const;
};
