#pragma once
#include "Component.h"

class MovementComponent : public Component
{

	Vector2f destination;
public:
	void SetDestination(const Vector2f& _destination)
	{
		destination = _destination;
	}
};

