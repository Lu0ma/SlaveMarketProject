#include "Camera.h"
#include "Game.h"
#include "ShapeWidget.h"
#include <ctime>
#include <cstdlib>
#include "TimerManager.h"

#include "Timer.h"

Camera::Camera() : Actor("Camera" , ShapeData())
{
	shake = new ShakeComponent(this);

	speed = 0.5f;
	axeX = 0.0f;
	axeY = 0.0f;
	dampX = 100.0f;
	dampY = 0.0f;

	targetPosition = Vector2f();
	offsetCamera = Vector2f(dampX * 0.75f,0.0f);
	offsetScreen = Vector2f();
	zoom = Vector2f();
	defaultSize = view.getSize();

	view = View();
	view.zoom(-1.01f);

	isDown = false;
	isZoom = false;
	isUp = false;
	canShake = false;
	canUpdate = true;
}


void Camera::MoveToTarget(const float _deltaTime)
{
	float _distance;
	if (IsAtDestination(_distance)) return;

	Vector2f _direction = targetPosition - view.getCenter();
	Normalize(_direction);
	view.move(_direction * speed * _deltaTime * abs(_distance * 0.01f));
}

bool Camera::IsAtDestination(float& _distance)
{
	_distance = Distance(view.getCenter(), targetPosition);
	return _distance <= 10.5f;
}

void Camera::Init()
{
	dampY = Game::GetWindowSize().y * 0.25f;
	view.setCenter(Game::GetPlayer()->GetShapePosition());
}

void Camera::ShakeActor(const float _deltaTime)
{
	if (!canShake) return;

	#pragma region Inits

	Vector2f _offset;
	int _randomX = Random<int>(400, 100);
	int _randomY = Random<int>(400 , 100);
	int _randomNeg = Random<int>(2, 1);

	#pragma endregion 

	_randomNeg == 1 ? _offset = Vector2f(static_cast<float>(_randomX), static_cast<float>(_randomY)) :
	_offset = Vector2f(static_cast<float>(-_randomX), static_cast<float>(-_randomY));
	targetPosition += _offset * _deltaTime;
}

void Camera::Update(const float _deltaTime)
{
	Player* _player = Game::GetPlayer();
	RenderWindow& _window = Game::GetWindow();
	const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offsetCamera.x : -offsetCamera.x;
	const float _distance = Distance(view.getCenter().y, _player->GetShapePosition().y);

	const float _lastPositionPlayer = _player->GetShapePosition().y;
	if (isDown)
	{
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, 400.0f));
		ShakeActor(_deltaTime);
	}
	else if (isUp)
	{
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, -400.0f));
		ShakeActor(_deltaTime);
	}
	else
	{
		targetPosition = Vector2f(Vector2f(_player->GetShapePosition().x, 0.0f) + Vector2f(_offsetX, canUpdate ? view.getCenter().y : _player->GetShapePosition().y));
		ShakeActor(_deltaTime);
	}


	if (_distance > dampY)
	{
		targetPosition.y = _player->GetShapePosition().y;
	}

	MoveToTarget(_deltaTime);
	UpdateViewSize(_deltaTime);
	shake->Update(view);
}

void Camera::ResetZoom(const float _deltaTime)
{
	if (view.getSize().x <= defaultSize.x)
	{
		view.setSize(view.getSize().x + axeX, view.getSize().y + axeY);
		axeX += 0.01f * _deltaTime;
		axeY += 0.01f * _deltaTime;
		return;
	}
	else if (view.getSize().x >= defaultSize.x)
	{
		axeX = 0.0f;
		axeY = 0.0f;
	}
}

void Camera::ZoomView(const float _deltaTime)
{
	zoom -= Vector2f(0.3f * _deltaTime, 0.3f * _deltaTime);
}

void Camera::UpdateViewSize(const float _deltaTime)
{
	if (!isZoom)
	{
		ResetZoom(_deltaTime);
	}

	else
	{
		const float _limits = defaultSize.x - 300;
		zoom = view.getSize();
		if (view.getSize().x <= _limits)
		{
			shake->Shake(0.01f, 10 * _deltaTime);
			return;
		}
		ZoomView(_deltaTime);
		view.setSize(zoom) ;
	}
}