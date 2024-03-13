#pragma once
#include "State.h"

#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

class DeathState : public State
{
protected:
	AnimationComponent* animation;
	MobMovementComponent* movement;
	InspectComponent* inspect;

public:
	DeathState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
};

