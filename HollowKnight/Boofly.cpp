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


	animation = new AnimationComponent(this, {
		AnimationData("Idle", Vector2f(0.0f, 17.0f), _size, _readDirection, _toRepeat, 5, _speed),
		AnimationData("Right", Vector2f(0.0f, 380.0f), _size, _readDirection, _toRepeat, 4, _speed),
		AnimationData("Bounce", Vector2f(42.0f, 745.0f), _sizeBounce, _readDirection, _toRepeat, 2, _speed),
		AnimationData("DeathAir", Vector2f(0.0f, 1120.0f), _sizeDeathAir, _readDirection, _toRepeat, 4, _speed),
		AnimationData("DeathLand", Vector2f(0.0f, 1480.0f), _sizeDeathLand, _readDirection, _toRepeat, 3, _speed),
	});

	components.push_back(animation);
}

void Boofly::Death()
{

}

void Boofly::Attack()
{

}
