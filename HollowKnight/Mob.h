#pragma once
#include "Enemy.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "MobAttackComponent.h"
#include "MobLifeComponent.h"

class Mob : public Enemy
{
	Vector2f startPosition;
	Vector2f goalPosition;

protected:
	bool isPatrolling;

	AnimationComponent* animation;
	MovementComponent* movement;
	MobAttackComponent* attack;
	MobLifeComponent* life;

public:
	MobLifeComponent* GetLife()const
	{
		return life;
	}

public:
	Mob(const ShapeData& _data);

private:
	void InitTimerPatrol();
	void RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent);

public:
	void Move();
	void Patrol();
	virtual void Death() = 0;
};