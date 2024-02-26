#pragma once
#include "Actor.h"
#include "PlayerStats.h"
#include "Inventory.h"

#include "Merchand.h"

using namespace std;

class Player : public Actor
{
	PlayerStats* stats;
	Inventory* inventory;

	//TODO move
	Merchand* merchand;

public:
	PlayerStats* GetStats() const
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
	void Init();
	void SetupPlayerInput();
	void InitStats();

public:
	virtual void Update(const float _deltaTime) override;
	void Init();
};