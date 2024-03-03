#pragma once
#include"Component.h"
#include"AnimationComponent.h"

class NPCAnimationComponent : public Component
{
	AnimationComponent* animation;
	vector<string> animNPC;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	NPCAnimationComponent(Actor* _owner);
};

