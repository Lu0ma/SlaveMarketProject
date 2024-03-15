#pragma once
#include "Mob.h"
#include <vector>

class DeathMob : public Mob
{
	vector<string> animDeath;
	string name;
	int death;

public:
	DeathMob(const string& _name,const ShapeData& _data);

public:
	void StandBy();
	void Action();

	virtual void Init() override;
	virtual void Update (const float _deltaTime)override;
	virtual void Attack(Player* _player) override;
	virtual void Death() override;
	bool IsDead();
};