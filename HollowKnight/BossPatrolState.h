#pragma once
#include "PatrolState.h"
#include "PatrolToChase.h"

class BossBrain;

class BossPatrolState : public PatrolState
{
	PatrolToChase* patrolToChase;

public:
	BossPatrolState(BossBrain* _brain);

public:
	virtual void Init() override;
};