#include "PatrolComponent.h"
#include "Actor.h"

PatrolComponent::PatrolComponent(Actor* _owner, const Vector2f& _offset) : MobMovementComponent(_owner)
{
	pauseDuration = 2.0f;
	startPosition = _owner->GetShapePosition();
	targetPosition = startPosition + _offset;
	patrolTimer = nullptr;
}


void PatrolComponent::ChangeTargetPosition()
{
	const bool _isAtDestination = GetDestination() == startPosition;
	SetDestination(_isAtDestination ? targetPosition : startPosition);
}


void PatrolComponent::Init()
{
 	SetCallback([&]()
	{
		SetCanMove(false);
		patrolTimer = new Timer([&]() { ChangeTargetPosition(); }, seconds(pauseDuration), true, false);
	});
}