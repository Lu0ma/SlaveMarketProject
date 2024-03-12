#pragma once
#include "Enemy.h"
#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "MobAttackComponent.h"
#include "InspectComponent.h"
#include "Game.h"

class Mob : public Enemy
{
protected:
	bool isPatrolling;
	bool cooldownAttack;

	MobMovementComponent* movement;
	MobAttackComponent* attack;
	InspectComponent* inspect;

public:
	Mob(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	virtual void Attack(Player* _player);
	virtual void Death();
};