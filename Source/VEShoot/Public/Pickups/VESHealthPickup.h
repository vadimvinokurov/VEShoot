// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/VESBasePickup.h"
#include "VESHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class VESHOOT_API AVESHealthPickup : public AVESBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 10.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
