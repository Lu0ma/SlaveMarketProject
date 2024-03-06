#pragma once
#include "Component.h"
#include "ShapeObject.h"

class CollisionComponent : public Component
{
	ShapeObject* boxCollision;

public:
	CollisionComponent(Actor* _owner);

public:
	void CheckCollision(Actor* _owner);
};