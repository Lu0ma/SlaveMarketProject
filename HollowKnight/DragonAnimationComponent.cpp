#include "DragonAnimationComponent.h"

DragonAnimationComponent::DragonAnimationComponent(Actor* _owner) : Component(_owner)
{
	animation = new AnimationComponent(_owner);
	animDragon.push_back("DanceRight");
	animDragon.push_back("DanceLeft");

	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("DanceLeft", Vector2f(0.0f, 476.0f), Vector2f(275.0f, 286.0f), READ_RIGHT, false, 8, _speed, true, "DanceRight"),
		AnimationData("DanceRight", Vector2f(0.0f, 53.0f), Vector2f(267.0f, 286.0f), READ_RIGHT, false, 8, _speed, true,"DanceLeft"),

		});
}

