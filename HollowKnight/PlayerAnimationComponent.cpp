#include "PlayerAnimationComponent.h"

PlayerAnimationComponent::PlayerAnimationComponent(Actor* _owner) : Component(_owner)
{
	animation = new AnimationComponent(_owner);
	animPlayer = vector<string>();
}

void PlayerAnimationComponent::Init()
{
	animPlayer.push_back("Right");
	animPlayer.push_back("StopRight");
	animPlayer.push_back("Left");
	animPlayer.push_back("StopLeft");
	animPlayer.push_back("Jump");
	animPlayer.push_back("Dash");
	animPlayer.push_back("Sit");
	animPlayer.push_back("RemoveMana");
	animPlayer.push_back("Special");

	const Vector2f& _size = Vector2f(80.0f, 80.0f);
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 8;// a changer
	const int _countAttack = 7;
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("Right", Vector2f(80.0f, 0.0f), _size, _readDirection, _toRepeat, 3, _speed),
		AnimationData("StopRight", Vector2f(0.0f, 0.0f), _size, _readDirection, _toRepeat, 1, _speed),
		AnimationData("Left", Vector2f(80.0f, 0.0f), _size, _readDirection, _toRepeat, 3, _speed, false),
		AnimationData("StopLeft", Vector2f(0.0f, 0.0f), _size, _readDirection, _toRepeat, 1, _speed, false),
		AnimationData("Jump", Vector2f(0.0f, 720.0f), Vector2f(79.0f, 71.0f), _readDirection, false, 9, 0.03f, true, "StopRight"),// Change size
		AnimationData("Dash", Vector2f(0.0f, 560.0f), _size, _readDirection, false, 11, _speed, false, "StopRight"),
		AnimationData("Sit", Vector2f(485.0f, 400.0f), Vector2f(79.0f, 71.0f), _readDirection, _toRepeat, 1, _speed),
		AnimationData("RemoveMana", Vector2f(330.0f, 240.0f), Vector2f(79.0f, 71.0f), _readDirection, _toRepeat, 3, _speed),
		AnimationData("Special", Vector2f(0.0f, 320.0f), _size, _readDirection, _toRepeat, _countAttack, _speed),
	});
}
