#pragma once
#include "Mob.h"

class Boofly : public Mob
{
public:
	Boofly(const ShapeData& _data);

public:
	virtual void Init() override;
};