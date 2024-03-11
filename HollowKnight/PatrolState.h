#pragma once
#include "State.h"

#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

class PatrolState : public State
{
	AnimationComponent* animation;
	MobMovementComponent* movement;
	InspectComponent* inspect;

	Vector2f startPosition;
	Vector2f goalPosition;

public:
	PatrolState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};