#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include "Inventory.h"
#include "PlayerMovementComponent.h"
#include"AnimationComponent.h"
#include<vector>
#include"Timer.h"
#include<functional>

using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	Inventory* inventory;
	PlayerMovementComponent* movement;
	AnimationComponent* animation;
	vector<string> animPlayer;
	Timer* deathTimer;

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
	void SetupPlayerInput();

public:
	void Init();
	void SpecialAttack();
	void Death();
};