#pragma once
#include"Component.h"
#include"AnimationComponent.h"

class LeverAnimationComponent : public Component
{
	vector<string> animLever;
	AnimationComponent* animation;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	LeverAnimationComponent(Actor* _owner);
};

