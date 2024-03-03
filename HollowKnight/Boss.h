#pragma once
#include "Actor.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "MobAttackComponent.h"
#include "MobLifeComponent.h"
#include "Game.h"

class Boss : public Actor
{
	Vector2f startPosition;

protected:
	AnimationComponent* animation;
	MovementComponent* movement;
	MobAttackComponent* attack;
	MobLifeComponent* life;
	
public:
	Boss(const ShapeData& _data);

public:
	void FacePlayer(Player* _player);
	virtual void Update(const float _deltaTime) override;
	virtual void Attack(Player* _player) = 0;
};