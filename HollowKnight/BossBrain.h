#pragma once
#include "EnemyBrain.h"
#include "BossPatrolState.h"
#include "BossAttackState.h"

class BossBrain : public EnemyBrain
{
	BossPatrolState* patrol;
	ChaseState* chase;
	BossAttackState* attack;

public:
	BossPatrolState* GetPatrolState() const
	{
		return patrol;
	}
	ChaseState* GetChaseState() const
	{
		return chase;
	}
	BossAttackState* GetAttackState() const
	{
		return attack;
	}

public:
	BossBrain(Actor* _owner);
	~BossBrain();

public:
	virtual void Init() override;
};