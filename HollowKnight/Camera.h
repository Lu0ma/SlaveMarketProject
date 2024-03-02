#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

enum Target
{
	TARGET_NONE , TARGET_PLAYER , TARGET_WINDOW
};

class Camera
{
	View view;
	Vector2f center;
	Vector2f size;
	Target target;

public:
	void SetTarget(const Target& _target)
	{
		target = _target;
	}
	void SetView(const View& _view)
	{
		view = _view;
	}
	void SetCenter(const Vector2f& _center)
	{
		center = _center;
	}
	void SetSize(const Vector2f& _size)
	{
		size = _size;
	}
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
	Target GetTargetStat() const
	{
		return target;
	}

public:
	Camera(const Target& _target);

private:
	FloatRect GetPlayerRect();

public:
	View FollowPlayer();
	void CheckCameraState(View& _newView);
};