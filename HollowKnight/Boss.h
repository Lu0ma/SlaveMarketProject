#pragma once
#include "Enemy.h"
#include "MobMovementComponent.h"
#include "PatrolComponent.h"
#include "MobAttackComponent.h"
#include "InspectComponent.h"
#include "Game.h"

class Boss : public Enemy
{
protected:
	MobMovementComponent* movement;
	PatrolComponent* patrol;
	MobAttackComponent* attack;
	InspectComponent* inspect;

public:
	Boss(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
};