#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VESHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VESHOOT_API UVESHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UVESHealthComponent();

	float GetHealth() const { return Health; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
