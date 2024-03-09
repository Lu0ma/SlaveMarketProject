#pragma once
#include "Actor.h"
#include "DragonAnimationComponent.h"

class Dragon : public Actor
{
	DragonAnimationComponent* animation;

public:
	DragonAnimationComponent* GetAnimation() const
	{
		return animation;
	}

public:
	Dragon(const ShapeData& _data);

public:
	void PlayMusic();
};

