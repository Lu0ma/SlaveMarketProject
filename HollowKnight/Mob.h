#pragma once
#include "Actor.h"
#include "AnimationComponent.h"

class Mob : public Actor
{
	Vector2f startPosition;
	Vector2f goalPosition;

protected:
	bool isPatrolling;

public:
	Mob(const ShapeData& _data);

public:
	void Move();
	void Patrol();

private:
	void InitTimerPatrol();
	void RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent);
	virtual void Death() = 0;
};

