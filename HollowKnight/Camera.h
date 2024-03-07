//#pragma once
//#include<SFML/Graphics.hpp>
//using namespace sf;
//
//enum Target
//{
//	TARGET_NONE , TARGET_PLAYER , TARGET_WINDOW
//};
//
//class Camera
//{
//	View view;
//	Vector2f center;
//	Vector2f size;
//	Target target;
//
//public:
//	void SetTarget(const Target& _target)
//	{
//		target = _target;
//	}
//	void SetView(const View& _view)
//	{
//		view = _view;
//	}
//	void SetCenter(const Vector2f& _center)
//	{
//		center = _center;
//	}
//	void SetSize(const Vector2f& _size)
//	{
//		size = _size;
//	}
//	View GetView() const
//	{
//		return view;
//	}
//	Vector2f GetCenter() const
//	{
//		return center;
//	}
//	Vector2f GetSize() const
//	{
//		return size;
//	}
//	Target GetTargetStat() const
//	{
//		return target;
//	}
//
//public:
//	Camera(const Target& _target);
//
//private:
//	FloatRect GetPlayerRect();
//
//public:
//	View FollowPlayer();
//	void CheckCameraState(View& _newView);
//
//	void Test(const Vector2f& _lastPosition , const Vector2f& _currentPosition);
//};
#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
#include "ShapeWidget.h"
enum Target
{
	TARGET_NONE, TARGET_PLAYER, TARGET_WINDOW
};

struct CameraAnimation
{
	Time current;
	Time max;
	float trauma;
};

class Camera
{
	//View invisibleView;
	Vector2f center;
	Vector2f size;
	Target target;
	int offset;

	CameraAnimation animation;
	View defaultView;
	float damp;

public:
	void SetOffeset(const float _offset)
	{
		offset = _offset;
	}

	/*View GetView() const
	{
		return view;
	}*/

	/*View GetViewEffect() const
	{
		return invisibleView;
	}*/
	View GetDefaultView() const
	{
		return defaultView;
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

	void SetTarget(const Target& _target)
	{
		target = _target;
	}

	/*void SetView(const View& _view)
	{
		view = _view;
	}*/

	void setCenter(const Vector2f& _center)
	{
		center = _center;
	}

	void SetSize(const Vector2f& _size)
	{
		size = _size;
	}

private:
	FloatRect GetPlayerRect();

public:

	Camera(const Target& _target);

public:
	void TargetPlayer(View& _view);

	void Update();

	void ShakeCamera(float _trauma, float _duration);

	//View MoveSlowly();
	//View MoveSlowlyLeft();
	View Stop();
	void Init();
	//void Reset();
	void ShakeCamera();
private:

	FloatRect GetPlayerRect();
};
