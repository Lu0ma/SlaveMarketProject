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

	Vector2f targetPosition;
	Vector2f offsetCamera;
	Vector2f offsetScreen;
	Vector2f defaultSize;


	View view;
	ShakeComponent* shake;


	bool isDown;
	bool isUp;
	bool isZoom;

	bool canShake;
	
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

	void SetIsUp(const bool _isUp)
	{
		isUp = _isUp;
	}

	void SetIsZoom(const bool _isZoom)
	{
		isZoom = _isZoom;
	}

	void SetCanShake(const bool _canShake)
	{
		canShake = _canShake;
	}

	void SetTarget(const Vector2f& _newTarget)
	{
		targetPosition = _newTarget;
	}
public:
	Camera();

private:
	void MoveToTarget(const float _deltaTime);
	bool IsAtDestination(float& _distance);
	void ShakeActor(const float _deltaTime);
	void ShakeScreen();
	void UpdateSizeView(const float _deltaTime);

public:
	void Init();
	void Shake(const float _trauma, const float _duration);
	void Update(const float _deltaTime);
};

