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
};

class Camera
{
	float speed;
	float damp;
	float oldScaleX;
	Vector2f targetPosition;
	Vector2f offset;
	View view;
	Shake shake;
	Vector2f center;

public:
	View GetView() const
	{
		return view;
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

	//TODO move in macro
	static inline float randn();
};