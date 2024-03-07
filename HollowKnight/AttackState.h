#pragma once
#include "State.h"
#include "AttackToChase.h"
#include "AttackToPatrol.h"

class AttackState : public State
{
	AttackToChase* attackToChase;
	AttackToPatrol* attackToPatrol;

public:
	AttackState(Brain* _brain); 

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};

