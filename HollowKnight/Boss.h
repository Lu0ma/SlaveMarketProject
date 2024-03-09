#pragma once
#include "Enemy.h"
#include "MobMovementComponent.h"
#include "AnimationComponent.h"
#include "MobAttackComponent.h"
#include "Game.h"
#include "BossBrain.h"

class Boss : public Enemy
{
protected:
	BossBrain* brain;
	MobMovementComponent* movement;
	MobAttackComponent* attack;
	
public:
	BossBrain* GetBrain()
	{
		return brain;
	}

public:
	Boss(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	virtual void Attack(Player* _player) = 0;
	virtual void Death() = 0;
};