#pragma once
#include "State.h"
#include "AnimationComponent.h"
#include "MobMovementComponent.h"

#include "PatrolToChase.h"

class PatrolState : public State
{
	AnimationComponent* animation;
	MobMovementComponent* movement;

	Vector2f startPosition;
	Vector2f goalPosition;

	PatrolToChase* patrolToChase;

public:
	PatrolState(Brain* _brain);

public:
	virtual void Init() override;
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};

