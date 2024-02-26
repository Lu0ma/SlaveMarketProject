#include "MovementComponent.h"
#include "Actor.h"
#include "Macro.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.5f;
	minRange = 0.5f;
	destination = Vector2f();
}


void MovementComponent::MoveToDestination(const float _deltaTime)
{
	if (!canMove) return;

	if (IsAtPosition())
	{
		if (callback)
		{
			callback();
		}

		canMove = false;
		return;
	}

	Shape* _shape = owner->GetDrawable();
	Vector2f _direction = destination - _shape->getPosition();
	Normalize(_direction);

	const Vector2f& _position = _shape->getPosition() + _direction * speed * _deltaTime;
	_shape->setPosition(_position);
}

bool MovementComponent::IsAtPosition() const
{
	return Distance(owner->GetShapePosition(), destination) <= minRange;
}


void MovementComponent::Update(const float _deltaTime)
{
	MoveToDestination(_deltaTime);
}
