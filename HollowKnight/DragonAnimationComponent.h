#pragma once
#include"Component.h"
#include"AnimationComponent.h"

class DragonAnimationComponent : public Component
{
	vector<string> animDragon;
	AnimationComponent* animation;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	DragonAnimationComponent(Actor* _owner);


};

