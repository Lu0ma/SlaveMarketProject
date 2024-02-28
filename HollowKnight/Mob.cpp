#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "TextureManager.h"
#include "Timer.h"

Mob::Mob(const ShapeData& _data) : Actor("Mob" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;
	goalPosition = startPosition + Vector2f(500.0f, 0.0f);

	MovementComponent* _movement = new MovementComponent(this);
	_movement->SetSpeed(0.1f);
	components.push_back(_movement);
	Move();
	InitTimer();
}

void Mob::Move()
{
	MovementComponent* _movementComponent = GetComponent<MovementComponent>();
	if (_movementComponent->GetCanMove())
	{
		_movementComponent->SetDestination(startPosition);
	}
}

void Mob::Patrol()
{
	MovementComponent* _movementComponent = GetComponent<MovementComponent>();
	AnimationComponent* _animationComponent = GetComponent<AnimationComponent>();
	const vector<string>& _animationNames = _animationComponent->GetAnimationNames();

 	if (!_movementComponent->GetCanMove())
	{
		return;
	}
	if (_movementComponent->IsAtPosition())
	{
		if (_movementComponent->GetDestination() == startPosition)
		{
			_animationComponent->RunAnimation("FlyRight");
			_movementComponent->SetDestination(goalPosition);
		}
		else
		{
			_animationComponent->RunAnimation("FlyLeft");
			_movementComponent->SetDestination(startPosition);
		}
	}
}

void Mob::InitTimer()
{
	new Timer(this , &Mob::Patrol, seconds(1.5f), true, true);
}
