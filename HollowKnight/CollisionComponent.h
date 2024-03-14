#pragma once
#include "Component.h"
#include "ShapeObject.h"
#include <functional>

enum CollisionType
{
	CT_NONE = 1,
	CT_OVERLAP,
	CT_BLOCK,
};

class CollisionComponent : public Component
{
	ShapeObject* boxCollision;
	CollisionType type;

public:
	ShapeObject* GetBoxCollision() const
	{
		return boxCollision;
	}
	CollisionType GetType() const
	{
		return type;
	}

public:
	CollisionComponent(Actor* _owner, const CollisionType& _type);
	~CollisionComponent();

public:
	bool CheckCollision(const Vector2f& _position);
	bool CheckCollision(const vector<Actor*>& _ignoredActors = vector<Actor*>());
};