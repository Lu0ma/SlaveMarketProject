#pragma once
#include "Enemy.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "MobAttackComponent.h"
#include "MobLifeComponent.h"
#include "Game.h"

class Boss : public Enemy
{
	Vector2f startPosition;
	Vector2f goalPosition;

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
	void Patrol();

private:
	void InitTimerPatrol();
	void RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent);


};