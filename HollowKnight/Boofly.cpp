#include "Boofly.h"
#include "MovementComponent.h"
#include "CollectableActor.h"
#include "TimerManager.h"

Boofly::Boofly(const ShapeData& _data) : Mob(_data)
{ 
	isPatrolling = true;
	life = new MobLifeComponent(this, 1);
}

void Boofly::Init()
{
	const Vector2f& _size = Vector2f(315.0f, 345.0f);
	const Vector2f& _sizeBounce = Vector2f(329.0f, 360.0f);
	const Vector2f& _sizeDeathAir = Vector2f(300.0f, 330.0f);
	const Vector2f& _sizeDeathLand = Vector2f(337.0f, 265.0f);
	const int _count = 4;
	const float _speed = 0.12f;
	const float _speedTurn = 0.09f;

	animation->InitAnimations(
		{
			AnimationData("Idle", Vector2f(0.0f, 17.0f), _size, READ_RIGHT, true, 5, _speed, ""),
			AnimationData("Running", Vector2f(0.0f, 17.0f), _size, READ_RIGHT, true, 5, _speed, ""),
			AnimationData("Turn", Vector2f(0.0f, 380.0f), _size, READ_RIGHT, false, 4, _speedTurn, "Idle"),
			AnimationData("Bounce", Vector2f(42.0f, 745.0f), _sizeBounce, READ_RIGHT, false, 2, 0.06f, "Idle"),
			//AnimationData("Bounce2", Vector2f(42.0f, 745.0f), _sizeBounce, READ_RIGHT, false, 1, 0.02f, "Idle"),
			AnimationData("Death Air", Vector2f(30.0f, 1125.0f), _sizeDeathAir, READ_RIGHT, true, 4, _speed, "Death Land"),
			AnimationData("Death Land", Vector2f(0.0f, 1480.0f), _sizeDeathLand, READ_RIGHT, false, 4, _speed),
		});
}