#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "Actor.h"
#include "Macro.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.5f;
	minRange = 0.5f;
	destination = _owner->GetShapePosition();
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
	Vector2f _direction = destination - _shape->getPosition( );
	//cout << destination->x << " " << destination->y << endl;
	Normalize(_direction);

	//AnimationComponent* _animationComponent = owner->GetComponent<AnimationComponent>();
	//if (_direction.x > 0) // il va a droite
	//{		
	//	_animationComponent->RunAnimation("GoRight");
	//}
	//else
	//{
	//	_animationComponent->RunAnimation("GoLeft");
	//}

	const Vector2f& _position = _shape->getPosition() + _direction * speed * _deltaTime;
	_shape->setPosition(_position);
	//cout << _position.x << " " << _position.y << endl;
}

bool MovementComponent::IsAtPosition() const
{
	return Distance(owner->GetShapePosition(), destination) <= minRange;
}


void MovementComponent::Update(const float _deltaTime)
{
	MoveToDestination(_deltaTime);
}
