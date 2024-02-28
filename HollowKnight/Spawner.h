#pragma once
#include "Mob.h"
#include "Boofly.h"
#include "Belfly.h"

class Spawner
{
	Boofly* boofly;
	Belfly* belfly;
	int index;

public:
	Spawner();

public:
	void Spawn();
};

