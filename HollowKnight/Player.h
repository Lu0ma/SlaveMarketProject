#pragma once
#include "Actor.h"
#include "PlayerStat.h"
#include "Inventory.h"

#include "Merchand.h"

using namespace std;

class Player : public Actor
{
	PlayerStat* stats;
	Inventory* inventory;

public:
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