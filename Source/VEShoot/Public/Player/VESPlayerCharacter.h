// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/VESBaseCharacter.h"
#include "VESPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 *
 */
UCLASS()
class VESHOOT_API AVESPlayerCharacter : public AVESBaseCharacter
{
	GENERATED_BODY()
public:
	AVESPlayerCharacter(const FObjectInitializer& ObjInit);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void OnDeath() override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);

	void MoveRight(float Amount);

	void OnStartRunning();

	void OnStopRunning();
};
