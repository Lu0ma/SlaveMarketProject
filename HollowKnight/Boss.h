#pragma once
#include "Actor.h"
#include "AnimationComponent.h"

class Boss : public Actor
{
	Vector2f startPosition;

protected:
	AnimationComponent* animation;
	
public:
	Boss(const ShapeData& _data);


};

