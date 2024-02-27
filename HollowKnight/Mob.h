#pragma once
#include "Actor.h"

class Mob : public Actor
{
	Vector2f startPosition;
	Vector2f goalPosition;
	int life;

public:
	int GetLife()const
	{
		return life;
	}

public:
	Mob(const ShapeData& _data);

public:
	void Move();
	void Patrol();
	void TakeDamages(const int _attack);

private:
	void InitTimer();
};

