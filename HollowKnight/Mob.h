#pragma once
#include "Actor.h"

class Mob : public Actor
{
	Vector2f startPosition;
	Vector2f goalPosition;

public:
	Mob(const ShapeData& _data);

public:
	void Move();
	void Patrol();

private:
	void InitTimer();
};

