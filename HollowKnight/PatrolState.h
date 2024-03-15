#pragma once
#include "State.h"
#include "PatrolToDeath.h"
#include "InspectComponent.h"

class PatrolState : public State
{
	PatrolToDeath* patrolToDeath;
	InspectComponent* inspect;

public:
	PatrolState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};