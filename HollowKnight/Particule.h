#pragma once
#include "Actor.h"
#include "Macro.h"

class Particule : public Actor
{
	Timer* timerIn;
	Timer* timerOut;

	Color* color;
public:
	Particule();

	Vector2f GetRandomDirection();
	
};