#pragma once
#include "Brain.h"
#include "DeathState.h"

class EnemyBrain : public Brain
{
public:
	DeathState* death;

public:
	DeathState* GetDeathState() const
	{
		return death;
	}

public:
	EnemyBrain(Actor* _owner);
};