// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VESBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class VESHOOT_API AVESBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AVESBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

private:
	APlayerController* AVESBaseWeapon::GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const; 
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd) const;
	void MakeShot();
};
