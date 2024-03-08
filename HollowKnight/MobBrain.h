#pragma once
#include "EnemyBrain.h"
#include "MobPatrolState.h"
#include "MobAttackState.h"

class MobBrain : public EnemyBrain
{
	MobPatrolState* patrol;
	MobAttackState* attack;

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

public:
	virtual void Init() override;
};