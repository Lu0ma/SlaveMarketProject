#pragma once
#include "Mob.h"


class Spawner
{

#include "BooFly.h"
#include"DeathMob.h"

class Spawner
{
	Boofly* boofly;
	DeathMob* deathMob;

	int index;

public:
	Spawner();

public:
	void Spawn();
};

