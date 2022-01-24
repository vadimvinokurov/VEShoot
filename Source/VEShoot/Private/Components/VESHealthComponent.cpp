

#include "Components/VESHealthComponent.h"


UVESHealthComponent::UVESHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UVESHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}
