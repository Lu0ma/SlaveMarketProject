#pragma once
#include "State.h"
#include "ChaseToPatrol.h"
#include "ChaseToAttack.h"
#include "ChaseToDeath.h"

#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

class ChaseState : public State
{
	AnimationComponent* animation;
	MobMovementComponent* movement;
	InspectComponent* inspect;

	ChaseToPatrol* chaseToPatrol;
	ChaseToAttack* chaseToAttack;
	ChaseToDeath* chaseToDeath;

private:
	Timer* chaseTimer;

public:
	ChaseState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};