

#include "Components/VESHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UVESHealthComponent::UVESHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UVESHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

// Called when the game starts
void UVESHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UVESHealthComponent::OnTakeAnyDamage);
	}
}

void UVESHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
		return;

	GetWorld()->GetTimerManager().ClearTimer(AutoHealthTimerHandle);

	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHealEnable)
	{
		GetWorld()->GetTimerManager().SetTimer(
			AutoHealthTimerHandle, this, &UVESHealthComponent::OnAutoHeal, AutoHealIncDelay, true, AutoHealDelay);
	}
}

void UVESHealthComponent::OnAutoHeal()
{
	SetHealth(Health + AutoHealIncValue);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoHealthTimerHandle);
	}
}

void UVESHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}