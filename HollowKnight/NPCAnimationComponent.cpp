#include "NPCAnimationComponent.h"

NPCAnimationComponent::NPCAnimationComponent(Actor* _owner) : Component(_owner)
{
	animation = new AnimationComponent(_owner);
	animNPC = vector<string>();

	animNPC.push_back("Stand");
	animNPC.push_back("Talk");

	const Vector2f& _sizeStand = Vector2f(53.0f, 76.0f);
	const Vector2f& _sizeTalk = Vector2f(57.0f, 76.0f);
	const float _speed = 0.2f;

	animation->InitAnimations({
		AnimationData("Stand", Vector2f(0.0f, 12.0f), _sizeStand, READ_RIGHT, true, 6, _speed),
		AnimationData("Talk", Vector2f(0.0f, 100.0f), _sizeTalk, READ_RIGHT, true, 6, _speed), 
		
		});
}
