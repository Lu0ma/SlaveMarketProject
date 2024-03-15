#pragma once
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "Kismet.h"


using namespace sf;

class InspectComponent : public Component
{
	HitInfo hitInfo;
	float viewRange;
	Actor* raycast;
	float factor;

public:
	HitInfo GetHitInfo() const
	{
		return hitInfo;
	}

public:
	InspectComponent(Actor* _owner, const float _viewRange);

public:
	bool HasTarget(const Vector2f& _position, Vector2f _destination);
	bool IsInRange();
};

