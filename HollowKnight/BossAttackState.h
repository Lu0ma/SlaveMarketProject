#pragma once
#include "AttackState.h"
#include "AttackToChase.h"

class BossAttackState : public AttackState
{
	AttackToChase* attackToChase;

public:
	BossAttackState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
};