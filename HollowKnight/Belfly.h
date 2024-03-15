#pragma once
#include "Mob.h"

class Belfly : public Mob
{
public:
	Belfly(const ShapeData& _data);

public:
	virtual void Init() override;
};

