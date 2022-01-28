// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/VESWeaponComponent.h"
#include "Weapon/VESBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/VESEquipFinishedAnimNotify.h"
#include "Animations/VESReloadFinishedAnimNotify.h"
#include "Animations/VESAnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UVESWeaponComponent::UVESWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UVESWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only 2 weapon items"));

	CurrentWeaponIndex = 0;
	InitAnimation();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UVESWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void UVESWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<AVESBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;
		Weapon->OnClipEmpty.AddUObject(this, &UVESWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UVESWeaponComponent::AttachWeaponToSocket(AVESBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UVESWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	// CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {  //
		return Data.WeaponClass == CurrentWeapon->GetClass();								  //
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void UVESWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	CurrentWeapon->StartFire();
}

void UVESWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

void UVESWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UVESWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UVESWeaponComponent::InitAnimation()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UVESEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UVESWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UVESReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
			checkNoEntry();
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &UVESWeaponComponent::OnReloadFinished);
	}
}

void UVESWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	EquipAnimInProgress = false;
}

void UVESWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;

	CurrentWeapon->ChangedClip();
	ReloadAnimInProgress = false;
}

bool UVESWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UVESWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UVESWeaponComponent::CanReload() const
{
	return CurrentWeapon &&			 //
		   !EquipAnimInProgress &&	 //
		   !ReloadAnimInProgress &&	 //
		   CurrentWeapon->CanReload();
}

void UVESWeaponComponent::OnEmptyClip()
{
	ChangedClip();
}

void UVESWeaponComponent::ChangedClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();

	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

void UVESWeaponComponent::Reload()
{
	ChangedClip();
}

bool UVESWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIDate();
		return true;
	}
	return false;
}

bool UVESWeaponComponent::GetAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoDate();
		return true;
	}
	return false;
}
