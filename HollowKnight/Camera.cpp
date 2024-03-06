#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
	damp = 100.0f;
	position = Vector2f(0.0f, 0.0f);
	offset = Vector2f(10.0f, 0.0f);
	window = nullptr;
}


FloatRect Camera::GetPlayerRect()
{
	return Game::GetPlayer()->GetDrawable()->getGlobalBounds();
}

void Camera::FollowPlayer()
{
	const FloatRect& _rectPlayer = GetPlayerRect();
	Player* _player = Game::GetPlayer();

	View _view = window->getDefaultView();

	const float _offset = _rectPlayer.left > 0.0f ? offset.x : -offset.x;
	_view.setCenter(_rectPlayer.left + _offset, _rectPlayer.top);
	position = Vector2f(_rectPlayer.left + _offset, _rectPlayer.top);
	SetView(_view);
}


void Camera::Init(RenderWindow* _window)
{
	window = _window;
	position = window->getView().getCenter();

	const Vector2f& _halfWindowSize = Game::GetWindowSize() / 2.0f;
	Canvas* _canvas = new Canvas("Camera");

	ShapeWidget* _ligneLeft = new ShapeWidget(ShapeData(_halfWindowSize + Vector2f(-damp, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	_ligneLeft->GetDrawable()->setFillColor(Color::Magenta);
	_canvas->AddWidget(_ligneLeft);

	ligneMiddle = new ShapeWidget(ShapeData(_halfWindowSize, Vector2f(1, SCREEN_HEIGHT)));
	ligneMiddle->GetDrawable()->setFillColor(Color::Red);
	_canvas->AddWidget(ligneMiddle);

	ShapeWidget* _ligneRight = new ShapeWidget(ShapeData(_halfWindowSize + Vector2f(damp, 0.0f), Vector2f(1, SCREEN_HEIGHT)));
	_ligneRight->GetDrawable()->setFillColor(Color::Magenta);
	_canvas->AddWidget(_ligneRight);
}

void Camera::Update()
{
	if (!window) return;

	Player* _player = Game::GetPlayer();
	View _view = GetView();

	//cout << "position" << " " << position.x << " " << position.y << endl;
	//cout << "getViewport" << " " << _view.getViewport().left << " " << _view.getViewport().top << endl;


	/*cout << "Position" << " " << _player->GetShapePosition().x << endl;
	cout << window->getSize().x + window->getView().getCenter().x << endl;*/

	//const float _centerX = _view.getCenter().x;
	// const float _centerX = _view->getTransform().transformRect(GetPlayerRect()).getPosition().x;
	const float _distance = Distance(_player->GetShapePosition(), window->getDefaultView().getCenter());
	cout << _player->GetShapePosition().x << " " << _distance << " " << window->getDefaultView().getCenter().x << endl;

	if (_distance > damp)
	{
		//cout << "_distance" << " " << _distance << endl;
		//cout << "Position" << " " << _player->GetShapePosition().x << endl;
		//_newView = View(_player->GetShapePosition() + Vector2f(_player->GetComponent<PlayerMovementComponent>()->GetDirection().x * 10.0f, 0.0f) , view->getSize());

		FollowPlayer();
	}
}