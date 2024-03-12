#include "Camera.h"
#include "Game.h"
#include "ShapeWidget.h"
#include <ctime>
#include <cstdlib>
#include "TimerManager.h"
#include "Macro.h"
Camera::Camera() : Actor("Camera" , ShapeData())
{
	shake = new ShakeComponent(this);
	Player* _player = Game::GetPlayer();
	speed = 0.5f;
	damp = 100.0f;
	targetPosition = Vector2f();
	offset = Vector2f(damp * 0.75f,0.0f);
	offset2 = Vector2f(_player->GetShapePosition());
	view = View();
	defaultView = View();
	isDown = false;
	defaultSize = view.getSize();
	axeX = 0.0f;
	axeY = 0.0f;
	isZoom = false;
	view.zoom(1.5f);
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

	
	//if (_distance > damp || oldScaleX != _newScaleX && oldScaleY != _newScaleY)
	//{
	//	 const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
	//	 targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
	//	 oldScaleX = _newScaleX;
	//	 oldScaleY = _newScaleY;
	//}
	
	const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
	targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
	oldScaleX = _newScaleX;
	MoveToTarget(_deltaTime);
	UpdateSizeView();

	#pragma region ShakeUpdate
	// Le tremblement est terminer 
	if (shake->current >= shake->max)
	{ 
		//_window.setView(defaultView);
		return;
	}
	float _angle = CAMERA_SHAKE_ANGLE * shake->trauma * Randn();
	offset2.x = CAMERA_SHAKE_OFFSET * shake->trauma * Randn();
	offset2.y = CAMERA_SHAKE_OFFSET * shake->trauma * Randn();
	view.setRotation(_angle);
	_window.setView(view);
	shake->current += milliseconds(100);
	float _ratio = shake->current.asSeconds() / shake->max.asSeconds();
	shake->trauma *= 1.0f - _ratio * _ratio;
	// ResetShake();
	
#pragma endregion
}

void Camera::UpdateSizeView()
{
	if (!isZoom)
	{
		if (view.getSize().x <= defaultSize.x)
		{
			view.setSize(view.getSize().x + axeX, view.getSize().y + axeY);
			axeX += 1.1f;
			axeY += 1.1f;
		}
	}
	else if(isZoom)
	{
		if (view.getSize().x <= defaultSize.x - 35) return;
		view.zoom(0.999f);
	}
}



