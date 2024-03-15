#pragma once
#include "State.h"
#include "AttackToDeath.h"
#include "InspectComponent.h"
#include "MobAttackComponent.h"

class AttackState : public State
{
	AttackToDeath* attackToDeath;
	InspectComponent* inspect;
	MobAttackComponent* attack;
protected:
	AnimationComponent* animation;

public:
	AttackState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};