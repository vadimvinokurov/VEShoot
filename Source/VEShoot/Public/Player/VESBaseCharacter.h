// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VESBaseCharacter.generated.h"


class UVESHealthComponent;
class UVESWeaponComponent;

UCLASS()
class VESHOOT_API AVESBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AVESBaseCharacter(const FObjectInitializer& ObjInit);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Teams")
	void SetPlayerColor(const FLinearColor& Color);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnDeath();

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Components")
	UVESHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Components")
	UVESWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeapthAnimMotage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10.f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

private:
	void OnHealthChanged(float Health, float DeltaHealth);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
