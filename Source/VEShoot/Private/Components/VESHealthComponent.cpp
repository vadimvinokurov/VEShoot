

#include "Components/VESHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

UVESHealthComponent::UVESHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UVESHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UVESHealthComponent::OnTakeAnyDamage);
	}

}

void UVESHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;

	UE_LOG(HealthComponentLog, Display, TEXT("Damage: %f"), Damage);
}
