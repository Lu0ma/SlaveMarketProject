#pragma once
#include"Actor.h"
#include"LeverAnimationComponent.h"

class Lever : public Actor
{
	LeverAnimationComponent* animation;

public:
	LeverAnimationComponent* GetAnimations()
	{
		return animation;
	}

public:
	Lever(const string& _name,const ShapeData& _data);
};

