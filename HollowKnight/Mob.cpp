#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "TextureManager.h"
#include "Timer.h"

Mob::Mob(const ShapeData& _data) : Actor("Mob" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;
	goalPosition = startPosition + Vector2f(500.0f, 0.0f);
	life = 25;

	isPatrolling = false;

	MovementComponent* _movement = new MovementComponent(this);
	_movement->SetSpeed(0.1f);
	components.push_back(_movement);
	InitTimerPatrol();
}


void Mob::InitTimerPatrol()
{
	new Timer(this, &Mob::Patrol, seconds(1.0f), true, true);
}

void Mob::RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent)
{
	_animationComponent->GetCurrentAnimation()->Stop();
	_animationComponent->RunAnimation(_linkedAnimation);
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

	if (isPatrolling)
	{
		if (_movementComponent->IsAtPosition())
		{
			const string& _linkedAnimation = _animationComponent->GetCurrentAnimation()->GetData().linkedAnimation;
			if (_linkedAnimation != "") RunLinkedAnimation(_linkedAnimation, _animationComponent);

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
}

void Mob::TakeDamages(const int _attack)
{
	life -= _attack;
}