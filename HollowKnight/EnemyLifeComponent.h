#pragma once
#include"Component.h"

class EnemyLifeComponent : public Component
{
	int life;

public:
	void SetLife(const int _life)
	{
		life = _life;
	}
	int GetLife() const
	{
		return life;
	}

public:
	EnemyLifeComponent(Actor* _owner, const int _life);

public:
	void TakeDamages(const int _damages);
};