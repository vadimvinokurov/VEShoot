#pragma once

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
};
