#pragma once
#include "State.h"
#include "AttackToDeath.h"

class AttackState : public State
{
protected:
	bool hasAttack;

	AttackToDeath* attackToDeath;

public:
	AttackState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};