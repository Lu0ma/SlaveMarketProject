#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class HuskBully : public Mob
{
public:
	HuskBully(const ShapeData& _data);

public:
	virtual void Init() override;
};