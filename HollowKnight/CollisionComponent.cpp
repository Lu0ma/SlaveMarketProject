#include "CollisionComponent.h"
#include "ActorManager.h"

bool CollisionComponent::CheckCollision(Actor* _currentActor)
{

	const vector<Actor*>& _allactors =  ActorManager::GetInstance().GetAllValues();
	Shape* _currentShape = _currentActor->GetShape();
	FloatRect _rect = _currentShape->getGlobalBounds();




	for (Actor* _actor : _allactors)
	{
		Shape* _shape = _actor->GetShape();
		if (_shape == _currentShape) continue;
		if (_rect.intersects(_shape->getGlobalBounds()))
		{
			
		}
	}

	return false;
}
