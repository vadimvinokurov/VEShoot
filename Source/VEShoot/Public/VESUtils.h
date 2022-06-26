#pragma once

#include "Player/VESPlayerState.h"

class VESUtils
{
public:
	template <typename T>
	static T* GetVESPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}

	static bool AreEnemies(AController* Controller1, AController* Controller2) { 
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<AVESPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<AVESPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}
};
