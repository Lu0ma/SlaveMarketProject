#pragma once
#include "State.h"

class AttackState : public State
{

public:
	AttackState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};