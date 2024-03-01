#pragma once
#include "Actor.h"
#include "AnimationComponent.h"
#include"MobAttackComponent.h"
#include"MobLifeComponent.h"

class Mob : public Actor
{
	Vector2f startPosition;
	Vector2f goalPosition;

protected:
	AnimationComponent* animation;
	MobAttackComponent* attack;
	MobLifeComponent* life;

protected:
	bool isPatrolling;

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