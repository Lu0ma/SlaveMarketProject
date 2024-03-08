#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define CAMERA_SHAKE_ANGLE 10.0f
#define CAMERA_SHAKE_OFFSET 20.0f

struct Shake
{
	Time current;
	Time max;
	float trauma;

	Shake()
	{
		current = Time();
		max = Time();
		trauma = 0;
	}
};
class Camera
{
	float speed;
	float damp;
	float oldScaleX;
	Vector2f targetPosition;
	Vector2f offset;
	Vector2f defaultSize;
	View view;
	Shake shake;
	bool isDown;

	bool isZoom;
	float axeX;
	float axeY;

public:
	View GetView() const
	{
		return view;
	}
public:
	void SetIsDown(const bool _isDown)
	{
		isDown = _isDown;
	}

	void SetAxeY(const float _axeY)
	{
		axeY = _axeY;
	}

	void SetIsZoom(const bool _isZoom)
	{
		isZoom = _isZoom;
	}
public:
	Camera();

private:
	void MoveToTarget(const float _deltaTime);
	bool IsAtDestination(float& _distance);

public:
	void Init();
	void Shake(const float _trauma, const float _duration);
	void Update(const float _deltaTime);

	void MoveCamera(const float _axeX , const float _axeY);
	void CheckIsDown();

	void Zoom();
	void ResetZoom();
	void UpdateSizeView();


};

