#pragma once
#include"Component.h"

class MobLifeComponent : public Component
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
	MobLifeComponent(Actor* _owner, const int _life);

public:
	void TakeDamages(const int _damages);

};

