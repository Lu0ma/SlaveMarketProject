#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Component.h"
#include "Macro.h"
using namespace sf;

#define CAMERA_SHAKE_ANGLE 10.0f
#define CAMERA_SHAKE_OFFSET 20.0f

struct ShakeComponent : public Component
{
	Time current;
	Time max;
	float trauma;
	Vector2f offsetScreen;
	ShakeComponent(Actor* _actor) : Component(_actor)
	{
		current = Time();
		max = Time();
		trauma = 0;
		offsetScreen = Vector2f();
	}


	void Shake(const float _trauma, const float _duration)
	{
		max = milliseconds(static_cast<Int32>(_duration));
		current = seconds(0);
		trauma += _trauma;
	}

	void Update(View& _view)
	{
		if (current >= max) return;
		float _angle = CAMERA_SHAKE_ANGLE * trauma * Randn();
		offsetScreen.x = CAMERA_SHAKE_OFFSET * trauma * Randn();
		offsetScreen.y = CAMERA_SHAKE_OFFSET * trauma * Randn();
		_view.setRotation(_angle);
		current += milliseconds(static_cast<Int32>(11.0f));
		const float _ratio = current.asSeconds() / max.asSeconds();
		trauma *= 1.0f - _ratio * _ratio;
	}
};

class Camera : public Actor
{
	float speed;
	float axeX;
	float axeY;
	float dampX;
	float dampY;

	Vector2f targetPosition;
	Vector2f offsetCamera;
	Vector2f offsetScreen;
	Vector2f defaultSize;

	Vector2f zoom;
	View view;
	ShakeComponent* shake;

	bool isDown;
	bool isUp;
	bool isZoom;
	bool canShake;
	bool canUpdate;

public:
	View GetView() const
	{
		return view;
	}
	ShakeComponent* GetShake() const
	{
		return shake;
	}
public:
	void SetIsDown(const bool _isDown)
	{
		isDown = _isDown;
	}

	void SetUpdate(const bool _canUpdate)
	{
		canUpdate = _canUpdate;
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
	void UpdateViewSize(const float _deltaTime);
	void ZoomView(const float _deltaTime);
	void ResetZoom(const float _deltaTime);
	void ShakeActor(const float _deltaTime);

public:
	void Init();
	void Update(const float _deltaTime);


};

