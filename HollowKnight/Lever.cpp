#include "Lever.h"

Lever::Lever(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	const Vector2f& _size = Vector2f(235.0f, 282.0f);
	const float _speed = 0.1f;

	InitAnimations({
		AnimationData("Up", Vector2f(0.0f, 149.0f), _size, READ_RIGHT, true, 1, _speed),
		AnimationData("Down", Vector2f(0.0f, 149.0f), _size, READ_RIGHT, false, 3, _speed),

		});
}
