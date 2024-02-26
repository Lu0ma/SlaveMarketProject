#include "Camera.h"
#include "Player.h"
//#include "Map.h"

Camera::Camera()
{
	center = Vector2f();
	size = Vector2f(1000 , 1000);
	view = View(center , size);
// 	view = View();
}

Camera::Camera(View _view)
{
	view = _view;
}

View Camera::FollowPlayer()
{

	Player* _player; // Ne pas creer de player mais le recuperer 
	const FloatRect& _rectP = _player->GetShape()->getGlobalBounds();
 	const Vector2f& _newMousePosition = Vector2f(_rectP.left, _rectP.top);
	
	//Uniquement si on Utilise la souris
	// SetMousePosition(_newMousePosition);

	view.setCenter(_rectP.left ,_rectP.top);
	return view;
}
