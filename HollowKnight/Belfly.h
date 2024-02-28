#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class Belfly : public Mob
{
	AnimationComponent* animation;

public:
	Belfly(const ShapeData& _data);
};

