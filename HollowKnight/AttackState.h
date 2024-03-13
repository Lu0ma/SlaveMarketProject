#pragma once
#include "State.h"
#include "AttackToDeath.h"

#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

class AttackState : public State
{
protected:
	AnimationComponent* animation;
	MobMovementComponent* movement;
	InspectComponent* inspect;
	bool hasAttack;

	AttackToDeath* attackToDeath;

public:
	AttackState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};