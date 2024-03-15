#pragma once
#include "Component.h"
#include "Timer.h"

class MobAttackComponent : public Component
{
	int damages;
	float cooldown;
	Timer* cooldownTimer;

private:
	bool IsAttacking() const
	{
		return cooldownTimer && cooldownTimer->IsRunning();
	}
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

private:
	void ApplyDamagesToPlayer();

public:
	void Attack();
	void StopAttack();
};