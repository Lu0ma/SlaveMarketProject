#include "Grub.h"

Grub::Grub(const string& _name, const ShapeData& _data, const vector<string>& _texts) : InteractableActor(STRING_ID("Grub"), _data)
{
	animation = new AnimationComponent(this);
	animGrub = vector<string>();

	animGrub.push_back("Jail");
	animGrub.push_back("Escape");
	animGrub.push_back("Escape2");

	const Vector2f& _sizeJail = Vector2f(116.0f, 135.0f);
	const Vector2f& _sizeEscape = Vector2f(113.0f, 173.0f);
	const Vector2f& _sizeEscape2 = Vector2f(137.0f, 173.0f);
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("Jail", Vector2f(16.0f, 18.0f), _sizeJail, READ_RIGHT, true, 13, _speed),
		AnimationData("Escape", Vector2f(2.0f, 175.0f), _sizeEscape, READ_RIGHT, false, 9, _speed,true, "Escape2"),
		AnimationData("Escape2", Vector2f(0.0f, 388.0f), _sizeEscape2, READ_RIGHT, false, 5, _speed),

		});
}
