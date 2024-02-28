#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class HuskBully : public Mob
{
	AnimationComponent* animation;

public:
	HuskBully(const ShapeData& _data);

};

