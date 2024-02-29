#pragma once
#include"Mob.h"
#include "AnimationComponent.h"

class DeathMob : public Mob
{
	AnimationComponent* animation;

public:
	DeathMob(const ShapeData& _data);

public:
	void StandBy();
	void Action();
	void Attack();
	virtual void Death()override;
};

