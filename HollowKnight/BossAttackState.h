#pragma once
#include "AttackState.h"
#include "AttackToChase.h"
#include "BossSoundComponent.h"
class BossAttackState : public AttackState
{
	AttackToChase* attackToChase;
	BossSoundComponent* sound;
public:
	BossAttackState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
};