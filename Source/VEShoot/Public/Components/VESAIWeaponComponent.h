// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VESWeaponComponent.h"
#include "VESAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class VESHOOT_API UVESAIWeaponComponent : public UVESWeaponComponent
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;

	virtual void NextWeapon() override;
};
