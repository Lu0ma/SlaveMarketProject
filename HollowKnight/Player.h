#pragma once
#include "InputManager.h"
#include "Merchand.h"

class Player
{
	Merchand* merchand;
public:
	Player();

	void InitInputs();
};

