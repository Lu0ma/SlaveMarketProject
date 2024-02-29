#pragma once
#include "Mob.h"
#include "BooFly.h"
#include "DeathMob.h"

class Spawner
{
	int index;
	Boofly* boofly;
	DeathMob* deathMob;

public:
	Spawner();

public:
	void Spawn();
};