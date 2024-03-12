#include "Camera.h"
#include "Game.h"
#include "ShapeWidget.h"
#include <ctime>
#include <cstdlib>
#include "TimerManager.h"
#include "Macro.h"
#include "Timer.h"
Camera::Camera() : Actor("Camera" , ShapeData())
{
	shake = new ShakeComponent(this);
	Player* _player = Game::GetPlayer();
	speed = 0.5f;
	damp = 100.0f;
	targetPosition = Vector2f();
	offset = Vector2f(damp * 0.75f,0.0f);
	offset2 = Vector2f(_player->GetPosition());
	view = View();
	defaultView = view;
	defaultSize = view.getSize();
	axeX = 0.0f;
	axeY = 0.0f;

	isDown = false;
	isZoom = false;
	isUp = false;
	canShake = false;
}




void Camera::MoveToTarget(const float _deltaTime)
{
	//	Player* _player = Game::GetPlayer();
	float _distance;
	if (IsAtDestination(_distance))
	{
		return;
	}
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
	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;
	Canvas* _canvas = new Canvas("Camera");

	ShapeWidget* _ligneLeft = new ShapeWidget(ShapeData(_halfWindowSize + Vector2f(-damp, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	_ligneLeft->GetDrawable()->setFillColor(Color::Magenta);
	_canvas->AddWidget(_ligneLeft);

	ShapeWidget* _ligneMiddle = new ShapeWidget(ShapeData(_halfWindowSize, Vector2f(1, SCREEN_HEIGHT)));
	_ligneMiddle->GetDrawable()->setFillColor(Color::Red);
	_canvas->AddWidget(_ligneMiddle);

	ShapeWidget* _ligneRight = new ShapeWidget(ShapeData(_halfWindowSize + Vector2f(damp, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	_ligneRight->GetDrawable()->setFillColor(Color::Magenta);
	_canvas->AddWidget(_ligneRight);
}

void Camera::Shake(const float _trauma, const float _duration)
{
	shake->max = milliseconds(static_cast<Int32>(_duration));
	shake->current = seconds(0);
	shake->trauma += _trauma;
}

void Camera::ShakeActor(const float _deltaTime)
{
	if (!canShake) return;
	Vector2f _offset;
	Player* _player = Game::GetPlayer();
	int _randomX = rand() % 30 + 1;
	int _randomY = rand() % 30 + 1;

	int _randomNeg = rand() % 2 + 1;
	if (_randomNeg == 1)
	{
	 _offset = Vector2f(static_cast<float>(_randomX), static_cast<float>(_randomY));
	}
	else
	{
		_offset = Vector2f(static_cast<float>(-_randomX), static_cast<float>(-_randomY));
	}


	Vector2f _newTargetPosition = Vector2f(targetPosition + _offset);
	// Normalize(_newTargetPosition);
	 view.setCenter(_newTargetPosition);

	// targetPosition += _newTargetPosition;
}

void Camera::ResetShake()
{
	shake->max = milliseconds(0);
	shake->current = seconds(0);
	shake->trauma = 0.0f;
}

void Camera::Update(const float _deltaTime)
{
	#pragma region Init
	RenderWindow& _window = Game::GetWindow();
	Player* _player = Game::GetPlayer();
	const float _distance = Distance(_player->GetShapePosition().x, view.getCenter().x);
	const float _newScaleX = Game::GetPlayer()->GetDrawable()->getScale().x;
	const float _newScaleY = Game::GetPlayer()->GetDrawable()->getScale().y;
#pragma endregion

	
	//if (_distance > damp || oldScaleX != _newScaleX)
	//{
	//	const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
	//	targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
	//}

	const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
	if (isDown)
	{
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, 400.0f));
	}
	else if (isUp)
	{
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, -400.0f));
	}
	else
	{
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
	}
	
	oldScaleX = _newScaleX;
	MoveToTarget(_deltaTime);
	ShakeActor(_deltaTime);
	UpdateSizeView(_deltaTime);

	#pragma region ShakeUpdate
	// Le tremblement est terminer 
	if (shake->current >= shake->max) return;
	float _angle = CAMERA_SHAKE_ANGLE * shake->trauma * Randn();
	offset2.x = CAMERA_SHAKE_OFFSET * shake->trauma * Randn();
	offset2.y = CAMERA_SHAKE_OFFSET * shake->trauma * Randn();
	view.setRotation(_angle);
	//_window.setView(view);
	shake->current += milliseconds(11.0f);
	float _ratio = shake->current.asSeconds() / shake->max.asSeconds();
	shake->trauma *= 1.0f - _ratio * _ratio;
	
#pragma endregion

}

void Camera::UpdateSizeView(const float _deltaTime)
{
	if (!isZoom)
	{
		if (view.getSize().x <= defaultSize.x)
		{
			view.setSize(view.getSize().x + axeX, view.getSize().y + axeY);
			axeX += 0.01f;
			axeY += 0.01f;
		}
	}
	else if(isZoom)
	{
		if (view.getSize().x <= defaultSize.x - 35) return;
		view.zoom(0.99999f);
	}
}



