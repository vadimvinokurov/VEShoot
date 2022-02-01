// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/VESProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/VESWeaponFXComponent.h"

AVESProjectile::AVESProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;

	WeaponFXComponent = CreateDefaultSubobject<UVESWeaponFXComponent>("WeaponFXComponent");
}

void AVESProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
	check(MovementComponent);
	check(WeaponFXComponent);

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AVESProjectile::OnProjectileHit);

	SetLifeSpan(LifeSeconds);
}

void AVESProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(),	 //
		DamageAmount,								 //
		GetActorLocation(),							 //
		DamageRadius,								 //
		StaticClass(),								 //
		{},								 //
		this,										 //
		GetController(),							 //
		DoFullDamage);

	WeaponFXComponent->PlayImpactFX(Hit);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);

	Destroy();
}

AController* AVESProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
