#include "Boofly.h"

#define PATH_BOOFLY "Animations/Boofly.png"

Boofly::Boofly(const ShapeData& _data) : Mob(_data)
{ 
	const Vector2f& _size = Vector2f(315.0f, 345.0f); 
	const Vector2f& _sizeBounce = Vector2f(300.0f, 360.0f); 
	const Vector2f& _sizeDeathAir = Vector2f(300.0f, 330.0f); 
	const Vector2f& _sizeDeathLand = Vector2f(337.0f, 265.0f); 
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 4;
	const float _speed = 0.15f;

	animation = new AnimationComponent(this, PATH_BOOFLY, 
		{
			AnimationData("Idle", Vector2f(0.0f, 17.0f), _size, _readDirection, ANIM_DIR_NONE, _toRepeat, 5, _speed),
			AnimationData("Right", Vector2f(0.0f, 380.0f), _size, _readDirection, ANIM_DIR_RIGHT, _toRepeat, 4, _speed),
			AnimationData("Bounce", Vector2f(42.0f, 745.0f), _sizeBounce, _readDirection, ANIM_DIR_UP, _toRepeat, 2, _speed),
			AnimationData("DeathAir", Vector2f(0.0f, 1120.0f), _sizeDeathAir, _readDirection, ANIM_DIR_LEFT, _toRepeat, 4, _speed),
			AnimationData("DeathLand", Vector2f(0.0f, 1480.0f), _sizeDeathLand, _readDirection, ANIM_DIR_DOWN, _toRepeat, 3, _speed),
		}, ANIM_DIR_NONE);

	components.push_back(animation);
}