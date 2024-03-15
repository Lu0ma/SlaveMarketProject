#pragma once
#include "Actor.h"
#include "MobLifeComponent.h"
#include "EnemyBrain.h"

enum EnemyType
{
	BOSS, MOB
};

enum MobType
{
	MOB1, MOB2
};

enum BossType
{
	FALSE_KNIGHT
};

class Enemy : public Actor
{
protected:
	EnemyBrain* brain;
	MobLifeComponent* life;
	bool isDead;

public:
	Enemy(const string& _name, const ShapeData& _data);

public:
	EnemyBrain* GetBrain()
	{
		return brain;
	}
	MobLifeComponent* GetLife()const
	{
		return life;
	}
	bool IsDead()
	{
		return isDead;
	}

public:
	virtual void Update(const float _deltaTime);
};

