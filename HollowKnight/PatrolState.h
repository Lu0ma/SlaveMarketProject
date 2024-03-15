#pragma once
#include "State.h"
#include "PatrolToDeath.h"

class PatrolState : public State
{
protected:
	Vector2f startPosition;
	Vector2f goalPosition;

	Timer* patrolTimer;
	

	PatrolToDeath* patrolToDeath;

public:
	PatrolState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};

bool operator!=(const HitInfo& _first, const HitInfo& _second);