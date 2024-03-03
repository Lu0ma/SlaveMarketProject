#include "Mob.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "TextureManager.h"
#include "Timer.h"

Mob::Mob(const ShapeData& _data) : Enemy("Mob" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;
	goalPosition = startPosition + Vector2f(500.0f, 0.0f);

	isPatrolling = false;

	animation = new AnimationComponent(this);
	components.push_back(animation);

	movement = new MovementComponent(this);
	movement->SetSpeed(0.1f);
	components.push_back(movement);
	
	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);

	InitTimerPatrol();
}

void Mob::InitTimerPatrol()
{
	new Timer(this, &Mob::Patrol, seconds(1.0f), true, true);
}

void Mob::RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent)
{
	_animationComponent->GetCurrentAnimation()->Stop();

	Vector2f _direction = movement->GetDestination();
	_direction -= GetPosition();
	Normalize(_direction);
	_animationComponent->RunAnimation(_linkedAnimation, _direction.x);
}

void Mob::Move()
{
	if (movement->GetCanMove())
	{
		movement->SetDestination(startPosition);
	}
}

void Mob::Patrol()
{
	if (isPatrolling)
	{
		if (movement->IsAtPosition())
		{
			if (Animation* _animation = animation->GetCurrentAnimation())
			{
				const string& _linkedAnimation = _animation->GetData().linkedAnimation;
				if (_linkedAnimation != "") RunLinkedAnimation(_linkedAnimation, animation);

				if (movement->GetDestination() == startPosition)
				{
					movement->SetDestination(goalPosition);
				}
				else
				{
					movement->SetDestination(startPosition);
				}
			}
		}
	}
}

