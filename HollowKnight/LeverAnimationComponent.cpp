#include "LeverAnimationComponent.h"

LeverAnimationComponent::LeverAnimationComponent(Actor* _owner)
	: Component(_owner)
{
	animation = new AnimationComponent(_owner);
	animLever.push_back("Up");
	animLever.push_back("Down");

	const Vector2f& _size = Vector2f(235.0f, 282.0f);
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("Up", Vector2f(0.0f, 149.0f), _size, READ_RIGHT, true, 1, _speed),
		AnimationData("Down", Vector2f(0.0f, 149.0f), _size, READ_RIGHT, false, 3, _speed),

		});
}
