#pragma once
#include "ShapeWidget.h"

class Camera
{
	float damp;
	Vector2f position;
	Vector2f offset;
	RenderWindow* window;

	ShapeWidget* ligneMiddle;

private:
	void SetView(const View& _view)
	{
		window->setView(_view);
	}
	View GetView()
	{
		return window->getView();
	}
	
public:
	Camera();

private:
	FloatRect GetPlayerRect();
	void FollowPlayer();

public:
	void Init(RenderWindow* _window);
	void Update();
};