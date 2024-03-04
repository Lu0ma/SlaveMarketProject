#pragma once
#include"Mob.h"
#include "AnimationComponent.h"
#include<vector>

class DeathMob : public Mob
{
	AnimationComponent* animation;
	vector<string> animDeath;
	string name;

public:
	DeathMob(const string& _name,const ShapeData& _data);

public:
	void StandBy();
	void Action();
	void Attack();

	virtual void Init() override;
	virtual void Death()override;
	virtual void Update(const float _deltaTime)override;
};

