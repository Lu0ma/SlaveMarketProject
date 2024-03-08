#include "CollisionComponent.h"
#include "Actor.h"
#include "ActorManager.h"
#include "Kismet.h"

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionType& _type) : Component(_owner)
{
	boxCollision = new ShapeObject(ShapeData(_owner->GetBounds().getPosition(),
											 _owner->GetBounds().getSize(),
											 ""));
	boxCollision->GetDrawable()->setFillColor(Color::Transparent);
	boxCollision->GetDrawable()->setOutlineThickness(-2.0f);
	boxCollision->GetDrawable()->setOutlineColor(Color::Red);
	type = _type;
}

Actor* CollisionComponent::CheckCollision()
{
	Shape* _shape = owner->GetDrawable();

	//test tous les actors
	for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	{
		//si c'est le player, continue
		if (_actor == owner) continue;
		//FloatRect _currentShape = _actor->GetComponent<CollisionComponent>()->GetBoxCollision()->GetDrawable()->getGlobalBounds();
		FloatRect _currentShape = _actor->GetDrawable()->getGlobalBounds();
		//si un entity collisionne avec le joueur
		if (_currentShape.intersects(_shape->getGlobalBounds()))
		{
			return _actor;
		}
	}
	return nullptr;
}

bool CollisionComponent::CheckCollision(const Vector2f& _position, const Vector2f& _destination, const vector<Shape*>& _ignoredShapes)
{
	Shape* _xLine = _ignoredShapes[0];
	Shape* _yLine = _ignoredShapes[1];

	Vector2f _direction = _destination - _position;
	Normalize(_direction);
	const float _distance = Distance(_position, _destination);
	HitInfo _hitInfo;
	
	const bool _hasHit = Raycast(_position, _direction, _distance, _hitInfo, { owner->GetDrawable(), _xLine, _yLine });

	if (_hasHit)
	{
		if (CollisionComponent* _collisionComponent = _hitInfo.actor->GetComponent<CollisionComponent>())
		{
			if (_collisionComponent->GetType() == CT_BLOCK)
			{
				cout << _collisionComponent->owner->GetID() << endl;
				return true;
			}
			
		}	
	}
	return false;	
}

