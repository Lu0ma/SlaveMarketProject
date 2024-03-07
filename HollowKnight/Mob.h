#pragma once
#include "Enemy.h"
#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "MobAttackComponent.h"
#include "MobLifeComponent.h"
#include "Game.h"
#include "MobBrain.h"

class Mob : public Enemy
{
protected:
	MobBrain* brain;

	bool isPatrolling;
	bool cooldownAttack;

	AnimationComponent* animation;
	MobMovementComponent* movement;
	MobAttackComponent* attack;

public:
	MobBrain* GetBrain()
	{
		return brain;
	}

public:
	Mob(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	virtual void Attack(Player* _player) = 0;
	virtual void Death() = 0;
};