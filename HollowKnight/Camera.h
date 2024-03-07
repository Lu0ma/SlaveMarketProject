#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Camera
{
	float speed;
	float damp;
	float oldScaleX;
	Vector2f targetPosition;
	Vector2f offset;
	View view;

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
	void Update(const float _deltaTime);
};