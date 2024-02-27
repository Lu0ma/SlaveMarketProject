#pragma once
#include "Actor.h"
#include "PlayerStats.h"
#include "Inventory.h"
#include "Merchand.h"
#include "PlayerMovementComponent.h"
using namespace std;

class Player : public Actor
{
	PlayerStats* stats;
	Inventory* inventory;
	//TODO move
	Merchand* merchand;
	PlayerMovementComponent* movement;
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
	void SetupPlayerInput();
	void InitStats();

public:
	virtual void Update(const float _deltaTime) override;
	void Init();

private:
	void Right();
	void Left();
	void Up();
};