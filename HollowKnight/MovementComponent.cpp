#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "Actor.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.5f;
	collision = _owner->GetComponent<CollisionComponent>();
}

void MovementComponent::SetCanMove(const bool _status)
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