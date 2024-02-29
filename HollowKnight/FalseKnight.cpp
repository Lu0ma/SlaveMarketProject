#include "FalseKnight.h"

FalseKnight::FalseKnight(const ShapeData& _data) : Boss(_data)
{
	animation = new AnimationComponent(this);
	components.push_back(animation);
}

void FalseKnight::Init()
{
	const Vector2f& _sizeIdle = Vector2f(625.0f, 419.0f);
	const float _speed = 0.15f;

	animation->InitAnimations({
		AnimationData("Idle", Vector2f(0.0f, 0.0f), _sizeIdle, READ_RIGHT, true, 5, _speed),
		});


}
