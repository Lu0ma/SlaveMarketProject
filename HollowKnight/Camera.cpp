#include "Camera.h"
#include "Game.h"
#include "ShapeWidget.h"
#include <ctime>
#include <cstdlib>
#include "TimerManager.h"
#include "Macro.h"
Camera::Camera()
{
	speed = 0.5f;
	damp = 100.0f;
	targetPosition = Vector2f();
	offset = Vector2f(damp * 0.75f, 0.0f);
	view = View();
	isDown = false;
	defaultSize = view.getSize();
	axeX = 0.0f;
	axeY = 0.0f;
	isZoom = false;
}




void Camera::MoveToTarget(const float _deltaTime)
{
//	Player* _player = Game::GetPlayer();
	float _distance;
	if (IsAtDestination(_distance))
	{
		return;
	}
	//targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(axeX, axeY));
	Vector2f _direction = targetPosition - view.getCenter();
	Normalize(_direction);
	view.move(_direction * speed * _deltaTime * abs(_distance * 0.01f));
}

bool Camera::IsAtDestination(float& _distance)
{
	_distance = Distance(view.getCenter().x, targetPosition.x);

	return Distance(view.getCenter().x, targetPosition.x) <= 11.0f;
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
	shake.max = milliseconds(static_cast<Int32>(_duration));
	shake.current = seconds(0);
	shake.trauma += _trauma;
}

void Camera::Update(const float _deltaTime)
{
	#pragma region Init
	RenderWindow& _window = Game::GetWindow();
	Player* _player = Game::GetPlayer();
	View _view = GetView();
	const float _distance = Distance(_player->GetShapePosition().x, view.getCenter().x);
	const float _newScaleX = Game::GetPlayer()->GetDrawable()->getScale().x;
#pragma endregion

	MoveToTarget(_deltaTime);
	if (_distance > damp || oldScaleX != _newScaleX)
	{
		 const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
		 targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
		 oldScaleX = _newScaleX;
	}
	UpdateSizeView();

#pragma region ShakeUpdate
	// Le tremblement est terminer 
	if (shake.current >= shake.max) return;
	float _angle = CAMERA_SHAKE_ANGLE * shake.trauma * Randn();
	offset.x = CAMERA_SHAKE_OFFSET * shake.trauma * Randn();
	offset.y = CAMERA_SHAKE_OFFSET * shake.trauma * Randn();
	view.setRotation(_angle);
	_window.setView(view);
	shake.current += milliseconds(100);
	float _ratio = shake.current.asSeconds() / shake.max.asSeconds();
	shake.trauma *= 1.0f - _ratio * _ratio;
#pragma endregion

}


void Camera::MoveCamera(const float _axeX, const float _axeY)
{
	Player* _player = Game::GetPlayer();
	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();
	float _distance;
	if (IsAtDestination(_distance)) return;
	targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_axeX, -_axeY));
	Vector2f _direction = targetPosition - view.getCenter();
	Normalize(_direction);
	view.move(_direction * (speed + 2.0f) * _deltaTime * abs(_distance * 0.01f));
}

void Camera::CheckIsDown()
{
	if (isDown)
	{
		isDown = false;
	}
	else
	{
		isDown = true;
	}
}

void Camera::Zoom()
{
	view.zoom(0.5f);
}

void Camera::ResetZoom()
{
	if (view.getSize() != defaultSize)
	{
		//if (view.getSize().x >= defaultSize.x && view.getSize().y >= defaultSize.y)
		//{
		//	view.setSize(view.getSize().x - axeX, view.getSize().y - axeY);
		//	axeX += 1.0f;
		//	axeY += 1.0f;
		//}
		/*else*/ if (view.getSize().x <= defaultSize.x && view.getSize().y <= defaultSize.y)
		{
			view.setSize(view.getSize().x +  axeX , view.getSize().y + axeY);
			axeX += 0.3f;
			axeY += 0.3f;
		}
		//cout << "Y : " << view.getSize().y << endl;
		//cout << "X : " << view.getSize().x << endl;
	}

	//cout << "Vue par defaut " << endl;
	//cout << "X :" << defaultSize.x << endl;
	//cout << "Y :" << defaultSize.y << endl;

	//cout << "Vue Actuelle " << endl;
	//cout << "X : " << view.getCenter().x << endl;
	//cout << "Y : " << view.getCenter().y << endl;
	
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
		if (view.getSize().x <= 925) return;
		view.zoom(0.999);
	}



}



