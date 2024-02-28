#include "Boofly.h"
#include "MovementComponent.h"

#define PATH_BOOFLY "Animations/Boofly.png"

Boofly::Boofly(const ShapeData& _data) : Mob(_data)
{ 
	isPatrolling = true;

	const Vector2f& _size = Vector2f(315.0f, 345.0f); 
	const Vector2f& _sizeBounce = Vector2f(300.0f, 360.0f); 
	const Vector2f& _sizeDeathAir = Vector2f(300.0f, 330.0f); 
	const Vector2f& _sizeDeathLand = Vector2f(337.0f, 265.0f); 
	const ReadDirection& _readDirection = READ_RIGHT;
	const bool _toRepeat = true;
	const int _count = 4;
	const float _speed = 0.12f;
	const float _speedTurn = 0.09f;

	AnimationComponent* _animation = new AnimationComponent(this, {
		AnimationData("GoLeft", Vector2f(0.0f, 17.0f), _size, _readDirection, _toRepeat, 5, _speed, true, "TurnToRight"),
		AnimationData("GoRight", Vector2f(0.0f, 17.0f), _size, _readDirection, _toRepeat, 5, _speed, false, "TurnToLeft"),
		AnimationData("TurnToLeft", Vector2f(0.0f, 380.0f), _size, _readDirection, false, 4, _speedTurn, true, "GoLeft"),
		AnimationData("TurnToRight", Vector2f(0.0f, 380.0f), _size, _readDirection, false, 4, _speedTurn, false, "GoRight"),
		AnimationData("BounceLeft", Vector2f(42.0f, 745.0f), _sizeBounce, _readDirection, false, 2, _speed),
		AnimationData("BounceRight", Vector2f(42.0f, 745.0f), _sizeBounce, _readDirection, false, 2, _speed, false),
		AnimationData("DeathAirLeft", Vector2f(0.0f, 1120.0f), _sizeDeathAir, _readDirection, _toRepeat, 4, _speed),
		AnimationData("DeathAirRight", Vector2f(0.0f, 1120.0f), _sizeDeathAir, _readDirection, _toRepeat, 4, _speed, false),
		AnimationData("DeathLand", Vector2f(0.0f, 1480.0f), _sizeDeathLand, _readDirection, false, 3, _speed),
	});

	components.push_back(_animation);
}