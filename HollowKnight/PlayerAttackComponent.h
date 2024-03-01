#pragma once
#include<iostream>
#include"Component.h"

using namespace std;

class PlayerAttackComponent : public Component
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
	PlayerAttackComponent(Actor* _owner,const int _damages);

public:
	void SpecialAttack();
};

