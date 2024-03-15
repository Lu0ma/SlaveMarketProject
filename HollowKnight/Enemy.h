#pragma once
#include "Actor.h"
#include "EnemyLifeComponent.h"
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
	bool isDead;
	EnemyBrain* brain;
	EnemyLifeComponent* life;

public:
	Enemy(const string& _name, const ShapeData& _data);

public:
	EnemyBrain* GetBrain() const
	{
		return brain;
	}
	EnemyLifeComponent* GetLife() const
	{
		return life;
	}
	bool IsDead() const
	{
		return isDead;
	}

public:
	virtual void Update(const float _deltaTime);
};

