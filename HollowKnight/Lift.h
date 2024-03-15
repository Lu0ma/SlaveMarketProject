#pragma once
#include "Actor.h"
#include"Lever.h"

enum LiftMovementStatus
{
	LMS_NONE,
	LMS_UP = -1,
	LMS_DOWN = 1
};

class Lift : public Actor
{
	float moveSpeed;
	float destinationUp;
	float destinationDown;
	LiftMovementStatus status;
	Lever* lever;

public:
	Lift(const ShapeData& _data);

private:
	void Move(const float _deltaTime);

public:
	virtual void Update(const float _deltaTime) override;
	void Interact();
};