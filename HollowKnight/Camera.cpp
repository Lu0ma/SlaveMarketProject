#include "Camera.h"
#include "Game.h"
#include "ShapeWidget.h"

Camera::Camera()
{
	speed = 0.5f;
	damp = 100.0f;
	targetPosition = Vector2f();
	offset = Vector2f(damp * 0.75f, 0.0f);
	view = View();
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
	_distance = Distance(view.getCenter().x, targetPosition.x);

	return Distance(view.getCenter().x, targetPosition.x) <= 10.0f;
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

void Camera::Update(const float _deltaTime)
{
	Player* _player = Game::GetPlayer();
	View _view = GetView();
	const float _distance = Distance(_player->GetShapePosition().x, view.getCenter().x);
	const float _newScaleX = Game::GetPlayer()->GetDrawable()->getScale().x;

	if (_distance > damp || oldScaleX != _newScaleX)
	{
		const float _offsetX = Game::GetPlayer()->GetDrawable()->getScale().x > 0.0f ? offset.x : -offset.x;
		targetPosition = Vector2f(_player->GetShapePosition() + Vector2f(_offsetX, offset.y));
		oldScaleX = _newScaleX;
	}

	MoveToTarget(_deltaTime);
}