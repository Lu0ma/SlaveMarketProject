#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class Boofly : public Mob
{
	AnimationComponent* animation;

public:
	Boofly(const ShapeData& _data);
};

