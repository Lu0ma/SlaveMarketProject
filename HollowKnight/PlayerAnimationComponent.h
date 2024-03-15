#pragma once
#include"Component.h"
#include"AnimationComponent.h"

class PlayerAnimationComponent : public Component
{
	AnimationComponent* animation;
	vector<string> animPlayer;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

	vector<string> GetAnimPlayer()const
	{
		return animPlayer;
	}

public:
	PlayerAnimationComponent(Actor* _owner);

public:
	void Init();
};

