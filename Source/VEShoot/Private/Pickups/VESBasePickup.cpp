// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/VESBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

// Sets default values
AVESBasePickup::AVESBasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void AVESBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerateRotationYaw();
}

// Called every frame
void AVESBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void AVESBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

bool AVESBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void AVESBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AVESBasePickup::Respawn, RespawnTime);
}

void AVESBasePickup::Respawn()
{
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AVESBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1 : -1;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
