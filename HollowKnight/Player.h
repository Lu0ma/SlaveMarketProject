#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include"PlayerAttackComponent.h"
#include "Inventory.h"
#include "PlayerMovementComponent.h"
#include"PlayerAnimationComponent.h"

#include "CharmsMenu.h"

#include"AnimationComponent.h"
#include<vector>
#include"Timer.h"
#include<functional>


using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	PlayerAttackComponent* attack;
	PlayerAnimationComponent* animation;
	Inventory* inventory;
	CharmsMenu* charmsMenu;
	PlayerMovementComponent* movement;
	Timer* deathTimer;

	bool isStanding;

public:
	void SetStatus(const bool _status)
	{
		movement->SetCanMove(_status);
	}
	PlayerStat* GetStats() const
	{
		return stats;
	}
	Inventory* GetInventory() const
	{
		return inventory;
	}

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void InitAnimations();
	void SetupPlayerInput();

public:
	virtual void Init() override;
	void Update();
};