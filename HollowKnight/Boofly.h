#pragma once
#include "Mob.h"
#include "AnimationComponent.h"

class Boofly : public Mob
{
public:
	Boofly(const ShapeData& _data);

private:
	void Attack();

public:
	virtual void Init() override;
	virtual void Death() override;
};