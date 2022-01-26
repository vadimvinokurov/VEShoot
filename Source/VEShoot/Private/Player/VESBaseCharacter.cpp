// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VESBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/VESCharacterMovementComponent.h"
#include "Components/VESHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
AVESBaseCharacter::AVESBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UVESCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UVESHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AVESBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AVESBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AVESBaseCharacter::OnHealthChanged);
	LandedDelegate.AddDynamic(this, &AVESBaseCharacter::OnGroundLanded);
}

void AVESBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	UE_LOG(BaseCharacterLog, Display, TEXT("FallVelocityZ: %f"), FallVelocityZ);

	if(FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath:: GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(BaseCharacterLog, Display, TEXT("FallVelocityZ: %f"), FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}

// Called every frame
void AVESBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVESBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AVESBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVESBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AVESBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AVESBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVESBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AVESBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AVESBaseCharacter::OnStopRunning);
}

bool AVESBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float AVESBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngularBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngularBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AVESBaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f)
		return;
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AVESBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)
		return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AVESBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AVESBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}


void AVESBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void AVESBaseCharacter::OnDeath() {
	UE_LOG(BaseCharacterLog, Display, TEXT("Player pogib %s"), *GetName());
	PlayAnimMontage(DeapthAnimMotage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

