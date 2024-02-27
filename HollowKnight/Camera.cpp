#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
	center = Vector2f(/* rectPlayer.left , rectPlayer.top */);
	size = Vector2f(1000 , 1000);
	view = View(center , size);
}

Camera::Camera(View _view)
{
	view = _view;
}

View Camera::FollowPlayer()
{
	view.setCenter(GetPlayerRect().left, GetPlayerRect().top);
	return view;
}

FloatRect Camera::GetPlayerRect()
{
	Player* _player = Game::GetPlayer(); // Ne pas creer de player mais le recuperer 
	const FloatRect& _rectP = _player->GetShape()->getGlobalBounds();
	return _rectP;
}
