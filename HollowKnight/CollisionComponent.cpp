#include "CollisionComponent.h"
#include "Actor.h"
#include "ActorManager.h"
#include "Kismet.h"

#include "Player.h"

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionType& _type) : Component(_owner)
{
	boxCollision = new ShapeObject(ShapeData(_owner->GetShapePosition(), _owner->GetShapeSize() * 0.8f, ""));
	boxCollision->GetDrawable()->setOrigin(_owner->GetBounds().getSize() / 2.0f);
	boxCollision->GetDrawable()->setFillColor(Color::Transparent);
	boxCollision->GetDrawable()->setOutlineThickness(-2.0f);

	if (_owner->GetID() == "Player")
	{
		boxCollision->GetDrawable()->setOutlineColor(Color::Blue);
	}
	else if (_owner->GetID() == "raycastlineY")
	{
		boxCollision->GetDrawable()->setOutlineColor(Color::Magenta);
	}

	else
	{
		boxCollision->GetDrawable()->setOutlineColor(Color::Red);
	}

	type = _type;
}

CollisionComponent::~CollisionComponent()
{
	delete boxCollision;
}


bool CollisionComponent::CheckCollision(const Vector2f& _position)
{
	return type == CT_BLOCK && boxCollision->GetDrawable()->getGlobalBounds().contains(_position);
}

bool CollisionComponent::CheckCollision(const vector<Actor*>& _ignoredActors)
{
	vector<Actor*> _actors = { owner };
	_actors.insert(_actors.end(), _ignoredActors.begin(), _ignoredActors.end());
	HitInfo _hitInfo;
	const bool _hasHit = BoxCast(boxCollision->GetDrawable()->getGlobalBounds(), _hitInfo, _actors);

	if (_hasHit)
	{
		if (CollisionComponent* _collisionComponent = _hitInfo.actor->GetComponent<CollisionComponent>())
		{
			if (_collisionComponent->GetType() == CT_BLOCK)
			{
				//cout << _collisionComponent->owner->GetID() << endl;
				return true;
			}
		}	
	}

	return false;	
}