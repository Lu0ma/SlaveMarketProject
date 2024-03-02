#pragma once
#include"Component.h"

class MobAttackComponent : public Component
{
	int damages;

public: 
	void SetDamages(const int _damages)
	{
		damages = _damages;
	}
	int GetDamages()const
	{
		return damages;
	}

public:
	MobAttackComponent(Actor* _owner, const int _damages);

public:
	void Attack();
};

