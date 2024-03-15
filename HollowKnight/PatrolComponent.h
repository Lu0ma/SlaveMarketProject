#pragma once
#include "MobMovementComponent.h"

class PatrolComponent : public MobMovementComponent
{
	float pauseDuration;
	Vector2f startPosition;
	Vector2f targetPosition;
	Timer* patrolTimer;

public:
	void SetTargetPosition(const Vector2f& _targetPosition)
	{
		targetPosition = _targetPosition;
	}

public:
	PatrolComponent(Actor* _owner, const Vector2f& _offset);

private:
	void ChangeTargetPosition();

public:
	virtual void Init() override;
};