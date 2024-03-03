#include "MerchandAnimationComponent.h"

MerchandAnimationComponent::MerchandAnimationComponent(Actor* _owner) : Component(_owner)
{
	animation = new AnimationComponent(_owner);
	animMerchand = vector<string>();

	animMerchand.push_back("Wait");
	animMerchand.push_back("Sell");

	const Vector2f& _sizeWait = Vector2f(203.0f, 196.0f);
	const Vector2f& _sizeSell = Vector2f(203.0f, 223.0f);
	const float _speed = 0.2f;

	animation->InitAnimations({
		AnimationData("Wait", Vector2f(0.0f, 84.0f), _sizeWait, READ_RIGHT, true, 5, _speed),
		AnimationData("Sell", Vector2f(0.0f, 294.0f), _sizeSell, READ_RIGHT, true, 5, _speed),

		});
}
