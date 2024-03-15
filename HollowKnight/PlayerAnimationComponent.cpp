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
	animPlayer.push_back("DoubleJump");
	animPlayer.push_back("Wall");
	animPlayer.push_back("Fall");
	animPlayer.push_back("HeadUp");
	animPlayer.push_back("HeadDown");
	animPlayer.push_back("Death");
	animPlayer.push_back("Revive");
	animPlayer.push_back("UpAttack");
	animPlayer.push_back("IsHitten");

	const Vector2f& _size = Vector2f(80.0f, 80.0f);
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("Right", Vector2f(80.0f, 33.0f), _size, READ_RIGHT, true, 3, _speed),
		AnimationData("StopRight", Vector2f(0.0f, 33.0f), _size, READ_RIGHT, true, 1, _speed), //TODO put FIRST
		AnimationData("Left", Vector2f(80.0f, 33.0f), _size, READ_RIGHT, true, 3, _speed),
		AnimationData("StopLeft", Vector2f(0.0f, 33.0f), _size, READ_RIGHT, true, 1, _speed),
		AnimationData("Jump", Vector2f(0.0f, 753.0f), Vector2f(79.0f, 71.0f), READ_RIGHT, false, 9, 0.03f, "StopRight"),
		AnimationData("Dash", Vector2f(0.0f, 593.0f), _size, READ_RIGHT, false, 7, 0.05f, "StopRight"),
		AnimationData("Sit", Vector2f(485.0f, 433.0f), Vector2f(79.0f, 71.0f), READ_RIGHT, true, 1, _speed),
		AnimationData("RemoveMana", Vector2f(330.0f, 273.0f), Vector2f(79.0f, 71.0f), READ_RIGHT, true, 3, _speed),
		AnimationData("Special", Vector2f(0.0f, 353.0f), _size, READ_RIGHT, true, 7, _speed),
		AnimationData("DoubleJump", Vector2f(0.0f, 998.0f), Vector2f(126.0f, 89.0f), READ_RIGHT, false, 5, _speed, "StopRight"),
		AnimationData("Wall", Vector2f(640.0f,273.0f), _size, READ_RIGHT, true, 4, _speed),
		AnimationData("Fall", Vector2f(0.0f, 1099.0f), Vector2f(85.0f, 92.0f), READ_RIGHT, true, 3, _speed),
		AnimationData("StopFall", Vector2f(255.0f, 1095.0f), Vector2f(85.0f, 92.0f), READ_RIGHT, false, 1, _speed, "StopFall"),
		AnimationData("HeadUp", Vector2f(240.0f, 671.0f), Vector2f(80.0f, 83.0f), READ_RIGHT, true, 1, _speed),
		AnimationData("HeadDown", Vector2f(644.0f, 1095.0f), Vector2f(91.0f, 91.0f), READ_RIGHT, true, 1, _speed),
		//AnimationData("HeadDown", Vector2f(1153.0f, 774.0f), Vector2f(56.0f, 89.0f), READ_RIGHT, true, 1, _speed),
		AnimationData("Death", Vector2f(999.0f, 151.0f), Vector2f(115.0f, 105.0f), READ_RIGHT, false, 4, 0.6f, "StopRight"),
		AnimationData("Revive", Vector2f(800.0f, 0.0f),_size, READ_RIGHT, false, 1, 0.3f, "StopRight"),
		AnimationData("UpAttack", Vector2f(889.0f, 650.0f),Vector2f(78.0f, 96.0f), READ_RIGHT, false, 7, 0.09f,"StopRight" ),
		AnimationData("IsHitten", Vector2f(1037.0f, 343.0f),Vector2f(60.0f, 78.0f), READ_RIGHT, false, 2, 0.2f, "StopRight"),
	});
}