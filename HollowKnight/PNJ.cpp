#include "PNJ.h"
#include "Macro.h"

PNJ::PNJ(const ShapeData& _data) : InteractableActor(STRING_ID("PNJ"), _data)
{
	/*animation = new AnimationComponent(this);
	components.push_back(animation);*/

	/*animation->AddNames({
		"Stand",
		"Talk"
	});*/

	const Vector2f& _sizeStand = Vector2f(53.0f, 76.0f);
	const Vector2f& _sizeTalk = Vector2f(57.0f, 76.0f);
	const float _speed = 0.2f;

	/*animation->InitAnimations({
		AnimationData("Stand", Vector2f(0.0f, 12.0f), _sizeStand, READ_RIGHT, true, 6, _speed),
		AnimationData("Talk", Vector2f(0.0f, 100.0f), _sizeTalk, READ_RIGHT, true, 6, _speed),
		});*/

	InitAnimations({
		AnimationData("Stand", Vector2f(0.0f, 12.0f), _sizeStand, READ_RIGHT, true, 6, _speed),
		AnimationData("Talk", Vector2f(0.0f, 100.0f), _sizeTalk, READ_RIGHT, true, 6, _speed),
		});
}

