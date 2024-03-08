#include "CollisionComponent.h"
#include "Actor.h"
#include "ActorManager.h"
#include "Kismet.h"

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionType& _type) : Component(_owner)
{
	boxCollision = new ShapeObject(ShapeData(_owner->GetBounds().getPosition(),
											 _owner->GetBounds().getSize(),
											 ""));
	boxCollision->GetDrawable()->setOutlineThickness(5.0f);
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

bool CollisionComponent::CheckCollision(const Vector2f& _position, const Vector2f& _destination)
{
	Vector2f _direction = _destination - _position;
	Normalize(_direction);
	const float _distance = Distance(_position, _destination);
	HitInfo _hitInfo;
	
	const bool _hasHit = Raycast(_position, _direction, _distance, _hitInfo, { owner->GetDrawable()});

	if (_hasHit)
	{
		if (CollisionComponent* _collisionComponent = _hitInfo.actor->GetComponent<CollisionComponent>())
		{
			if (_collisionComponent->GetType() == CT_BLOCK) //ne passe jamais dans ce if
			{
				cout << _collisionComponent->owner->GetID() << endl;
				return true;
			}
		}	
	}
	return false;

	//test tous les actors
	//for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	//{
	//	//si c'est le player, continue
	//	if (_actor == owner) continue;
	//	//FloatRect _currentShape = _actor->GetComponent<CollisionComponent>()->GetBoxCollision()->GetDrawable()->getGlobalBounds();
	//	FloatRect _currentShape = _actor->GetDrawable()->getGlobalBounds();
	//	//si un entity collisionne avec le joueur
	//	if (_currentShape.contains(_position))
	//	{
	//		if (_actor->GetComponent<CollisionComponent>()->GetType() == CT_NONE)
	//		{
	//			cout << _actor->GetID() << endl;
	//			continue;
	//		}	
	//		else 
	//		{
	//			return _actor;
	//		}
	//	}
	//}
	//return nullptr;
	
}

