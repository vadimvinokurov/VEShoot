// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VESBaseCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/VESCharacterMovementComponent.h"
#include "Components/VESHealthComponent.h"
#include "Components/VESWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
AVESBaseCharacter::AVESBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UVESCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UVESHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UVESWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AVESBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AVESBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AVESBaseCharacter::OnHealthChanged);
	LandedDelegate.AddDynamic(this, &AVESBaseCharacter::OnGroundLanded);
}

void AVESBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	UE_LOG(BaseCharacterLog, Display, TEXT("FallVelocityZ: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("FallVelocityZ: %f"), FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}

// Called every frame
void AVESBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AVESBaseCharacter::IsRunning() const
{
	return false;
}

float AVESBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngularBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngularBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AVESBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance) return;
	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

void AVESBaseCharacter::OnHealthChanged(float Health, float DeltaHealth)
{

}

void AVESBaseCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("Player pogib %s"), *GetName());
	//PlayAnimMontage(DeapthAnimMotage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}
