#pragma once
#include "AttackState.h"

class BossBrain;

class BossAttackState : public AttackState
{
	AttackToChase* attackToChase;

public:
	BossAttackState(BossBrain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};