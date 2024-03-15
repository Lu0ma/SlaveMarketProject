#pragma once
#include "Component.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"

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
	Vector2f lastDirection;

	AnimationComponent* animation;
	CollisionComponent* collision;

public:
	void SetSpeed(const float _speed)
	{
		speed = _speed;
	}
	void SetCanMove(const bool _status);
	bool GetCanMove() const
	{
		return canMove;
	}
	Vector2f GetLastDirection() const
	{
		return lastDirection;
	}

public:
	MovementComponent(Actor* _owner);
};