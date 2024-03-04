#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace sf;

class MovementComponent : public Component
{
protected:
	bool canMove;
	float speed;
	float gravity;

public:
	void SetSpeed(const float _speed)
	{
		speed = _speed;
	}
	void SetCanMove(const bool _status)
	{
		canMove = _status;
	}	
	bool GetCanMove() const
	{
		return canMove;
	}

public:
	MovementComponent(Actor* _owner);

};