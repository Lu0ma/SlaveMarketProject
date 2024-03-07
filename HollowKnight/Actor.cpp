#include "Actor.h"
#include "ActorManager.h"
#include "Timer.h"
#include "CollisionComponent.h"

Actor::Actor(const string& _name, const ShapeData& _data, const CollisionType& _collisionType)
		   : ShapeObject(_data), IManagable(_name)
{
	Register();
	SetOriginAtMiddle(GetDrawable());

	CollisionComponent* _collision = new CollisionComponent(this, _collisionType);
	components.push_back(_collision);
}

Actor::~Actor()
{
	for (Component* _component : components)
	{
		delete _component;
	}
}

void Actor::Register()
{
	ActorManager::GetInstance().Add(id, this);
}


void Actor::Update(const float _deltaTime)
{
	for (Component* _component : components)
	{
		_component->Update(_deltaTime);
	}
	
}

void Actor::Destroy(const float _waitingTime)
{
	new Timer([&]() { SetToRemove(true); }, seconds(_waitingTime));
}