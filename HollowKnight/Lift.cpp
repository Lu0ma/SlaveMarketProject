#include "Lift.h"
#include "Macro.h"

#include "Game.h"

Lift::Lift(const ShapeData& _data) : Actor(STRING_ID("Lift"), _data, CT_NONE)
{
	moveSpeed = 2.0f;
	destinationUp = _data.position.y - 500.0f;
	destinationDown = _data.position.y;
	status = LMS_NONE;
	lever = new Lever( STRING_ID("Lever"), ShapeData(Vector2f(_data.position + Vector2f(-200.0f, -450.0f)), Vector2f(100.0f, 100.0f) , "Animations/Lever.png"));
	lever->GetDrawable()->setFillColor(Color::Green);
}


void Lift::Move(const float _deltaTime)
{
	const float _destinationY = status == LMS_UP ? destinationUp : destinationDown;
	const Vector2f& _destination = Vector2f(0.0f, _destinationY);

	Vector2f _direction = _destination - Vector2f(0.0f, GetShapePosition().y);
	if (_direction == Vector2f(0.0f, 0.0f)) return;

	Normalize(_direction);
	GetDrawable()->move(_direction * _deltaTime);

	if (status == LMS_DOWN)
	{
		Game::GetPlayer()->GetDrawable()->move(_direction * _deltaTime);
	}
}


void Lift::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	if (status != LMS_NONE)
	{
		Move(_deltaTime);
	}
}

void Lift::Interact()
{
	const Vector2f& _playerPos = Game::GetPlayer()->GetShapePosition();
	if (Distance(_playerPos, GetShapePosition()) <= 50.0f)
	{
		status = LMS_DOWN;
	}

	else if (Distance(_playerPos, lever->GetShapePosition()) <= 50.0f)
	{
		status = LMS_UP;
		lever->GetComponent<AnimationComponent>()->RunAnimation("Down", 1.0f);
	}
}