#pragma once
#include "State.h"
#include "ChaseToPatrol.h"
#include "ChaseToAttack.h"

class ChaseState : public State
{
	ChaseToPatrol* chaseToPatrol;
	ChaseToAttack* chaseToAttack;

public:
	ChaseState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};