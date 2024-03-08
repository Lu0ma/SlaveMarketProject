#pragma once
#include "EnemyBrain.h"

class MobBrain : public EnemyBrain
{
	PatrolState* patrol;
	AttackState* attack;

public:
	PatrolState* GetPatrolState() const
	{
		return patrol;
	}
	AttackState* GetAttackState() const
	{
		return attack;
	}

public:
	MobBrain(Actor* _owner);
};

