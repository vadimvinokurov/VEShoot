// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VESProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class VESHOOT_API AVESProjectile : public AActor
{
	GENERATED_BODY()

public:
	AVESProjectile();

	void SetShotDirection(const FVector& Direction)
	{
		ShotDirection = Direction;
		ShotDirection.Normalize();
	}

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool DoFullDamage = true;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float LifeSeconds = 50.f;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	AController* GetController() const;
};
