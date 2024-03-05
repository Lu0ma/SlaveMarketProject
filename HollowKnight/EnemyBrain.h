#pragma once
#include "Brain.h"
#include "PatrolState.h"
#include "AttackState.h"

class EnemyBrain : public Brain
{
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
	EnemyBrain(Actor* _owner);
	~EnemyBrain();
};

