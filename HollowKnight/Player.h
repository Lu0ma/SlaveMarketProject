#pragma once
#include "Actor.h"
#include "Inventory.h"

class Player : public Actor
{
	Inventory* inventory;

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void SetupPlayerInputs();

public:
	void Init();
};