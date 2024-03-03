#pragma once
#include"Component.h"
#include"AnimationComponent.h"

class MerchandAnimationComponent : public Component
{
	AnimationComponent* animation;
	vector<string> animMerchand;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	MerchandAnimationComponent(Actor* _owner);
};

