#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
	target = TARGET_NONE;
	const FloatRect& _rect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();
	center = Vector2f(_rect.left, _rect.top);
	size = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	view = View(center , size);
}

Camera::Camera(View _view)
{
	view = _view;
}

Camera::Camera(const Target& _target)
{
	target = _target;
	const FloatRect& _rect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();
	center = Vector2f(_rect.left, _rect.top);
	size = Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	view = View(center, size);
}

View Camera::FollowPlayer()
{
	const FloatRect& _rect = GetPlayerRect();
	view.setCenter(_rect.left, _rect.top);
	return view;
}

FloatRect Camera::GetPlayerRect()
{
	return Game::GetPlayer()->GetDrawable()->getGlobalBounds();
}
