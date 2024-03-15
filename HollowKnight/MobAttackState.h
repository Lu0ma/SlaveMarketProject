#pragma once
#include "AttackState.h"
#include "AttackToPatrol.h"

class MobAttackState : public AttackState
{
	AttackToPatrol* attackToPatrol;

public:
	MobAttackState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
};