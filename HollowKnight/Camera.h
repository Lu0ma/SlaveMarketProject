#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
#include "Player.h"

class Camera
{
	View view;
	Vector2f  center; // faudrait le centrer sur Le player
	Vector2f  size; // ???

public:
	View GetView() const
	{
		return view;
	}

	Vector2f GetCenter() const
	{
		return center;
	}

	Vector2f GetSize() const
	{
		return size;
	}
public:
	Camera();
	Camera(View _view);
public:
	void SetView(const View& _view)
	{
		view = _view;
	}
	void setCenter(const Vector2f& _center)
	{
		center = _center;
	}
	void SetSize(const Vector2f& _size)
	{
		size = _size;
	}
public:
	View FollowPlayer();
private:
	FloatRect GetPlayerRect();
};


