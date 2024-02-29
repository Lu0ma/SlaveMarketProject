#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class Boofly : public Mob
{
public:
	Boofly(const ShapeData& _data);

public:
	virtual void Death() override;
};

