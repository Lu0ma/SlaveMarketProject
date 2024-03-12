#include "Grub.h"
#include "Macro.h"

Grub::Grub(const ShapeData& _data) : Actor(STRING_ID("Grub"), _data)
{
	
	const Vector2f& _sizeJail = Vector2f(120.0f, 141.0f);
	const Vector2f& _sizeEscape = Vector2f(113.0f, 173.0f);
	const Vector2f& _sizeEscape2 = Vector2f(137.0f, 173.0f);
	const float _speed = 0.1f;

	InitAnimations(
		{ AnimationData("Jail", Vector2f(0.0f, 20.0f), _sizeJail, READ_RIGHT, true, 13, _speed),
		AnimationData("Escape", Vector2f(2.0f, 175.0f), _sizeEscape, READ_RIGHT, false, 9, _speed, "Escape2"),
		AnimationData("Escape2", Vector2f(0.0f, 388.0f), _sizeEscape2, READ_RIGHT, false, 5, _speed),
		});
}
