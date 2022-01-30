

#include "Components/VESHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"

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
	check(CameraShake);

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
	PlayCameraShake();
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
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UVESHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;
	
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}
