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
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
};
