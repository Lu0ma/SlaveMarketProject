#include "CollisionComponent.h"
#include "ActorManager.h"
#include "Player.h"
bool CollisionComponent::CheckCollision(Actor* _currentActor)
{

	const vector<Actor*>& _allActors =  ActorManager::GetInstance().GetAllValues();
	Shape* _currentShape = _currentActor->GetShape();
	FloatRect _rect = _currentShape->getGlobalBounds();

	for (Actor* _actor : _allActors)
	{
		Shape* _shape = _actor->GetShape();
		if (_shape == _currentShape) continue;
		if (_rect.intersects(_shape->getGlobalBounds()))
		{
			if (_actor != dynamic_cast<Actor*>(_actor))
			{
				cout << "je rentre dans le if" << endl;
				// Execute callback 
				// _actor.
			}
		}
	}

	return false;
}
