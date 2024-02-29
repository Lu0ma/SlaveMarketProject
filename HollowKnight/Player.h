#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include "Inventory.h"
#include "CharmsMenu.h"
#include "PlayerMovementComponent.h"
#include "Bench.h"

using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	Inventory* inventory;
	CharmsMenu* charmsMenu;
	PlayerMovementComponent* movement;

	Bench* bench;
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
	void SetupPlayerInput();

public:
	void Init();
};