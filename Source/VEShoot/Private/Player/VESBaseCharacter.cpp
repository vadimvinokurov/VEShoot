// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/VESBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
// Sets default values
AVESBaseCharacter::AVESBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AVESBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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
}

void AVESBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AVESBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}
