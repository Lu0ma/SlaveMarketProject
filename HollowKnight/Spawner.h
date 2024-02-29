#pragma once
#include "Mob.h"
#include "BooFly.h"
#include"DeathMob.h"

class Spawner
{
	Boofly* boofly;
	DeathMob* deathMob;
	int index;
	vector<string> animationNames;

public:
	Spawner();

public:
	void Spawn();
};

