#include "Camera.h"
#include "Game.h"

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
	//view.setCenter(_rect.left, view.getCenter().y);
	return view;
}

FloatRect Camera::GetPlayerRect()
{
	return Game::GetPlayer()->GetDrawable()->getGlobalBounds();
}

void Camera::CheckCameraState(View& _newView)
{
	RenderWindow& _window = Game::GetWindow();
	if (GetTargetStat() == TARGET_PLAYER)
	{
		_newView =FollowPlayer();
		_window.setView(_newView);
	}

	else if (GetTargetStat() == TARGET_WINDOW)
	{
		_newView = _window.getDefaultView();
		_window.setView(_newView);
	}
}
