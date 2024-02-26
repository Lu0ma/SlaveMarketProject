#pragma once
#include "InputManager.h"
#include "Merchand.h"
#include "Actor.h"
#include "Component.h"
class Player : public Actor
{
	ShapeData data;
	Merchand* merchand;

public:
	Player();

private:
	void Init();

private:
	void Right();
	void Left();
	void Up();
};

