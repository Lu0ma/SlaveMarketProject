#pragma once
#include "Component.h"
#include "PlayerAnimationComponent.h"

using namespace std;

class PlayerAttackComponent : public Component
{
	int damages;
	PlayerAnimationComponent* animation;

public:
	void SetDamages(const int _damages)
	{
		damages = _damages;
	}
	int GetDamages() const
	{
		return damages;
	}

public:
	PlayerAttackComponent(Actor* _owner,const int _damages);

public:
	void SpecialAttack();
};

