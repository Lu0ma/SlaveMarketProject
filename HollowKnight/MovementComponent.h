#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "AnimationComponent.h"

using namespace std;
using namespace sf;

class MovementComponent : public Component
{
	AnimationComponent* animation;

protected:
	bool canMove;
	float speed;
	float gravity;
	
	Vector2f lastDirection;

public:
	void SetSpeed(const float _speed)
	{
		speed = _speed;
	}
	void SetCanMove(const bool _status)
	{
		canMove = _status;
		if (!animation)
		{
			animation = owner->GetComponent<AnimationComponent>();
			if (!animation) return;
		}
		if (!canMove)
		{
			animation->RunAnimation("Idle", lastDirection.x);
		}

	}	
	bool GetCanMove() const
	{
		return canMove;
	}

public:
	MovementComponent(Actor* _owner);

};