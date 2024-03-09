#pragma once
#include "Actor.h"
#include "AnimationComponent.h"

class Grub : public Actor
{
	AnimationComponent* animation;
	vector<string> animGrub;

public:
	AnimationComponent* GetCurrentAnimation()const
	{
		return animation;
	}

public:
	Grub(const ShapeData& _data);
};

