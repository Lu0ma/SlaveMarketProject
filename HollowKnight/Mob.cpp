#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "TextureManager.h"
#include "Timer.h"

Mob::Mob(const ShapeData& _data) : Actor("Mob" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;
	goalPosition = startPosition + Vector2f(500.0f, 0.0f);

	//components.push_back(new MovementComponent(this));
	//Move();
	InitTimer();
}

void Mob::Move()
{
	MovementComponent* _movementComponent = GetComponent<MovementComponent>();

	Vector2f _destination = startPosition;

	_movementComponent->SetDestination(_destination);
}

void Mob::Patrol()
{
	MovementComponent* _movementComponent = GetComponent<MovementComponent>();

	if (_movementComponent->IsAtPosition())
	{
		if (_movementComponent->GetDestination() == startPosition)
		{
			_movementComponent->SetDestination(goalPosition);
		}
		else
		{
			_movementComponent->SetDestination(startPosition);
		}
	}
}

void Mob::InitTimer()
{
	//new Timer(this , &Mob::Patrol, seconds(1.5f), true, true);
}
