#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESCoreTypes.h"

#include "VESHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class VESHOOT_API UVESHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVESHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthProcent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	bool TryToAddHealth(float HealthAmount);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHealEnable = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHealEnable"))
	float AutoHealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHealEnable"))
	float AutoHealIncValue = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHealEnable"))
	float AutoHealIncDelay = 0.3f;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	FTimerHandle AutoHealthTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void OnAutoHeal();

	void SetHealth(float NewHealth);

	bool IsHealthFull() const { return Health == MaxHealth; }
};
