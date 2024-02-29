#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class Belfly : public Mob
{
public:
	Belfly(const ShapeData& _data);

public:
	virtual void Init() override;
	virtual void Death() override;
};

