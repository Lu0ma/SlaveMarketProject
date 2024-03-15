#pragma once
#include "Enemy.h"
#include "MobMovementComponent.h"
#include "PatrolComponent.h"
#include "InspectComponent.h"
#include "MobAttackComponent.h"

class Player;

class Mob : public Enemy
{
protected:
	bool isPatrolling;
	bool cooldownAttack;

	MobMovementComponent* movement;
	PatrolComponent* patrol;
	InspectComponent* inspect;
	MobAttackComponent* attack;

public:
	Mob(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	virtual void Attack(Player* _player);
	virtual void Death();
};