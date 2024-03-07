//#include "Camera.h"
//#include "Game.h"
//
//Camera::Camera(const Target& _target)
//{
//	target = _target;
//	const FloatRect& _rect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();
//	center = Vector2f(_rect.left, _rect.top);
//	size = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
//	view = View(center, size * 1.25f);
//}
//
//View Camera::FollowPlayer()
//{
//	const FloatRect& _rect = GetPlayerRect();
//	view.setCenter(_rect.left, _rect.top);
//	//view.setCenter(_rect.left, view.getCenter().y);
//	return view;
//}
//
//FloatRect Camera::GetPlayerRect()
//{
//	return Game::GetPlayer()->GetDrawable()->getGlobalBounds();
//}
//
//void Camera::CheckCameraState(View& _newView)
//{
//	RenderWindow& _window = Game::GetWindow();
//	if (GetTargetStat() == TARGET_PLAYER)
//	{
//		_newView = FollowPlayer();
//		_window.setView(_newView);
//	}
//
//	else if (GetTargetStat() == TARGET_WINDOW)
//	{
//		_newView = _window.getDefaultView();
//		_window.setView(_newView);
//	}
//}
#include "Camera.h"
#include "Game.h"
#include "Timer.h"
#include "Macro.h"
#include <functional>


FloatRect Camera::GetPlayerRect()
{
	return Game::GetPlayer()->GetDrawable()->getGlobalBounds();
}

Camera::Camera(const Target& _target)
{
	const RenderWindow& _window = Game::GetWindow();
	target = _target;
	center = Vector2f(static_cast<Vector2f>(_window.getPosition()));
	size = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	//view = View(center, size);
	//invisibleView = View(center, size);
	//invisibleView = View(view.getCenter() + Vector2f(50.0, 0.0f) , Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	offset = 10.0f;
	damp = 500.0f;
	defaultView = View(center, size);
}

void Camera::TargetPlayer(View& _view)
{
	const FloatRect& _rectPlayer = GetPlayerRect();
	Player* _player = Game::GetPlayer();
	if (_view.getCenter() != _player->GetShapePosition())
	{
		_view.move(offset, 0.0f);
	}
	const float _offset = _rectPlayer.left > 0.0f ? offset : -offset;
	_view.setCenter(_rectPlayer.left + _offset, _rectPlayer.top);
}



//View Camera::MoveSlowly()
//{
//	Vector2f _currentView = view.getCenter();
//	const FloatRect& _rectPlayer = GetPlayerRect();
//	Player* _player = Game::GetPlayer();
//
//	Vector2f _lastPositionPlayer = _player->GetLastPosition();
//	_lastPositionPlayer.x;
//
//	//if(_lastPositionPlayer.x < view.getCenter().x + 10)
//	//{
//	//	// view.move(-1.0f, 0.0f);
//	//}
//	//else if (_lastPositionPlayer.x > view.getCenter().x)
//	//{
//	//	view.move(3.0f, 0.0f);
//	//}
//	//if (view.getCenter().x <= _player->GetShapePosition().x)
//	//{
//	//}
//	if (view.getCenter().x >= invisibleView.getCenter().x + 300)
//	{
//		cout << "detecter" << endl;
//		return view;
//	}
//		view.move(3.0f, 0.0f);
//		return view;
//
//	//else if (view.getCenter().x >= _player->GetShapePosition().x)
//	//{
//	//	view.move(-3.0f, 0.0f);
//	//	return view;
//	//}
//
//}

//View Camera::MoveSlowlyLeft()
//{
//	Vector2f _currentView = view.getCenter();
//	const FloatRect& _rectPlayer = GetPlayerRect();
//	Player* _player = Game::GetPlayer();
//
//	Vector2f _lastPositionPlayer = _player->GetLastPosition();
//	_lastPositionPlayer.x;
//
//	//if(_lastPositionPlayer.x < view.getCenter().x + 10)
//	//{
//	//	// view.move(-1.0f, 0.0f);
//	//}
//	//else if (_lastPositionPlayer.x > view.getCenter().x)
//	//{
//	//	view.move(3.0f, 0.0f);
//	//}
//	if (view.getCenter().x <= _player->GetShapePosition().x)
//	{
//		view.move(-3.0f, 0.0f);
//		return view;
//	}
//	//else if (view.getCenter().x >= _player->GetShapePosition().x)
//	//{
//	//	view.move(-3.0f, 0.0f);
//	//	return view;
//	//}
//
//}

//View Camera::Stop()
//{
//}

void Camera::Init()
{
	Vector2f _size = Game::GetWindowSize();
	ShapeWidget* _ligneMiddle = new ShapeWidget(ShapeData(_size / 2.0f + Vector2f(50.0f, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	ShapeWidget* _ligneRight = new ShapeWidget(ShapeData(_size / 2.0f + Vector2f(150.0f, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	ShapeWidget* _ligneLeft = new ShapeWidget(ShapeData(_size / 2.0f + Vector2f(-50.0f, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	Canvas* _canvas = new Canvas("Camera");
	_canvas->AddWidget(_ligneMiddle);
	_canvas->AddWidget(_ligneRight);
	_canvas->AddWidget(_ligneLeft);
}

//void Camera::Reset()
//{
//	view.reset(FloatRect(center, size));
//}


void Camera::Update()
{
	RenderWindow& _window = Game::GetWindow();
	View _view = _window.getView();
	View _windowView = _window.getView();
	Player* _player = Game::GetPlayer();

	//if (GetTargetStat() == TARGET_PLAYER)
	//{
	//	//_newView = TargetPlayer();
	//	//_window.setView(_newView);
	//
	//	if (_player->GetDirection() == D_RIGHT)
	//	{
	//		const FloatRect& _rectPlayer = GetPlayerRect();

	//		 _newView = MoveSlowly();
	//		 _window.setView(_newView);
	//	}
	//	else if (_player->GetDirection() == D_LEFT)
	//	{
	//		_newView = MoveSlowlyLeft();
	// 		_window.setView(_newView);
	//	}
	//	else if (_player->GetDirection() == D_NONE)
	//	{
	// 		_newView = TargetPlayer();
	//		_newView = Stop();
	// 		_window.setView(_newView);
	//		//Reset();
	//	}

	//}
	//else if (GetTargetStat() == TARGET_WINDOW)
	//{
	//	_newView = _window.getDefaultView();
	//	_window.setView(_newView);
	//}

	const float _centerX = _view.getCenter().x;
	// const float _centerX = _view.getTransform().transformRect(GetPlayerRect()).getPosition().x;
	const float _distance = Distance(_player->GetShapePosition().x, _centerX);
	if (_distance > damp)
	{
		//cout << _distance << endl;
		cout << _player->GetShapePosition().x << endl;
		//_newView = View(_player->GetShapePosition() + Vector2f(_player->GetComponent<PlayerMovementComponent>()->GetDirection().x * 10.0f, 0.0f) , view.getSize());

		TargetPlayer(_view);
	}
	//else
	//{
	//	_newView = _window.getDefaultView();
	//	_window.setView(_newView);
	//}

	_window.setView(_view);
	if (_distance < _window.getDefaultView().getSize().x)
	{
		cout << "Tu as depasser les limites " << endl;
		_view = View(_player->GetShapePosition(), _view.getSize());
		// _newView.move(Vector2f(10.f, 0.0f));
		_window.setView(_view);
	}
}

void Camera::ShakeCamera(float _trauma, float _duration)
{
	animation.max = milliseconds(_duration);
	animation.current = seconds(0);
	animation.trauma += _trauma;
}

