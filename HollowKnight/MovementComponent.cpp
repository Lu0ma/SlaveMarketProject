#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "Actor.h"
#include "Macro.h"

MovementComponent::MovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.5f;
	gravity = 0.3f;
}
