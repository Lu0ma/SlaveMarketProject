#pragma once
#include "Mob.h"
#include "BooFly.h"

class Spawner
{
	Boofly* boofly;
	int index;
	vector<string> animationNames;

public:
	Spawner();

public:
	void Spawn();
};

