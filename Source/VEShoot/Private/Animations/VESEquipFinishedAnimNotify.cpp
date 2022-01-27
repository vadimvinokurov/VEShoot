// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/VESEquipFinishedAnimNotify.h"

 void UVESEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	 OnNotified.Broadcast(MeshComp);
	 Super::Notify(MeshComp, Animation);
 }
