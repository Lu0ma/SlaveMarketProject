#pragma once
#include "Actor.h"
#include "MobLifeComponent.h"

class Enemy : public Actor
{
protected:
	MobLifeComponent* life;
	bool isDead;

public:
	Enemy(const string& _name, const ShapeData& _data);

public:
	MobLifeComponent* GetLife()const
	{
		return life;
	}
	bool IsDead()
	{
		return isDead;
	}
};

