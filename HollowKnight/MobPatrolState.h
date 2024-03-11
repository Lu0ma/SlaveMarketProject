#pragma once
#include "PatrolState.h"
#include "PatrolToAttack.h"

class MobPatrolState : public PatrolState
{
	PatrolToAttack* patrolToAttack;

public:
	MobPatrolState(Brain* _brain);

public:
	virtual void Init() override;
};