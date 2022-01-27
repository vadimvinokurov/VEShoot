// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VESProjectile.generated.h"

class USphereComponent;

UCLASS()
class VESHOOT_API AVESProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AVESProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
};
