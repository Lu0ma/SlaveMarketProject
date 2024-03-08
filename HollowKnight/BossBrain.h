#pragma once
#include "EnemyBrain.h"
#include "BossPatrolState.h"
#include "BossAttackState.h"

class BossBrain : public EnemyBrain
{
	ChaseState* chase;
	BossPatrolState* patrol;
	BossAttackState* attack;

public:
	ChaseState* GetChaseState() const
	{
		return chase;
	}
	BossPatrolState* GetPatrolState() const
	{
		return patrol;
	}
	BossAttackState* GetAttackState() const
	{
		return attack;
	}

public:
	BossBrain(Actor* _owner);
	~BossBrain();
};