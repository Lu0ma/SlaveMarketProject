#pragma once
#include "State.h"
#include "AttackToChase.h"
#include "AttackToPatrol.h"

class EnemyBrain;

class AttackState : public State
{
protected:
	AttackToPatrol* attackToPatrol;

public:
	AttackState(EnemyBrain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};

