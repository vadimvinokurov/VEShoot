// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VESPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/VESWeaponComponent.h"

AVESPlayerCharacter::AVESPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	SpringArmComponent->TargetArmLength = 400.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void AVESPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVESPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVESPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AVESPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AVESPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVESPlayerCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AVESPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AVESPlayerCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UVESWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UVESWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UVESWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UVESWeaponComponent::Reload);
}


void AVESPlayerCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f) return;
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AVESPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AVESPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AVESPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool AVESPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AVESPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}