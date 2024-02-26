#pragma once
#include "Actor.h"
#include "Component.h"
class Player : public Actor
{
	ShapeData data;

public :
	Player();


public:
	void Init();

private:
	void Right();
	void Left();
	void Up();
};

