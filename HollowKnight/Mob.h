#pragma once
#include "Actor.h"
#include "AnimationComponent.h"

class Mob : public Actor
{
	Vector2f startPosition;
	Vector2f goalPosition;
	int life;
	int damages;

public:
	int GetLife()const
	{
		return life;
	}
	void SetLife(const int _life)
	{
		life = _life;
	}
	int GetDamages()const
	{
		return damages;
	}

protected:
	bool isPatrolling;

public:
	Mob(const ShapeData& _data);

public:
	void Move();
	void Patrol();
	void TakeDamages(const int _attack);
	virtual void Death() = 0;

private:
	void InitTimerPatrol();
	void RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent);
	virtual void Death() = 0;
};

