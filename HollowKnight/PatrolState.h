#pragma once
#include "State.h"
#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

#include "PatrolToAttack.h"

class MobBrain;

class PatrolState : public State
{
	AnimationComponent* animation;
	MobMovementComponent* movement;
	InspectComponent* inspect;

	Vector2f startPosition;
	Vector2f goalPosition;

	PatrolToAttack* patrolToAttack;

public:
	PatrolState(MobBrain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};