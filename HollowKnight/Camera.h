#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Component.h"
using namespace sf;

#define CAMERA_SHAKE_ANGLE 10.0f
#define CAMERA_SHAKE_OFFSET 20.0f

struct ShakeComponent : public Component
{
	Time current;
	Time max;
	float trauma;

	ShakeComponent(Actor* _actor) : Component(_actor)
	{
		current = Time();
		max = Time();
		trauma = 0;
	}
};

class Camera : public Actor
{
	float speed;
	float damp;
	float oldScaleX;
	float oldScaleY;
	Vector2f targetPosition;
	Vector2f offset;
	Vector2f offset2;
	Vector2f defaultSize;
	View view;
	View defaultView;
	ShakeComponent* shake;
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
	void ResetShake();
	void Update(const float _deltaTime);


	void UpdateSizeView();
};

