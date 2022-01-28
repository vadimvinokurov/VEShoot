#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimationNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimationNotify) return AnimationNotify;
		}
		return nullptr;
	}
};