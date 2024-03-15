#include "Actor.h"
#include "ActorManager.h"
#include "Timer.h"
#include "Macro.h"

Actor::Actor(const string& _name, const ShapeData& _data, const CollisionType& _collisionType)
		   : ShapeObject(_data), IManagable(_name)
{
	Register();
	SetOriginAtMiddle(GetDrawable());

	animation = new AnimationComponent(this);
	components.push_back(animation);

	collision = new CollisionComponent(this, _collisionType);
	components.push_back(collision);

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


void Actor::Init()
{
	for (Component* _component : components)
	{
		_component->Init();
	}
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

void Actor::InitAnimations(const vector<AnimationData>& _animations)
{
	vector<string> _animName;
	for (const AnimationData& _anim : _animations)
	{
		_animName.push_back(_anim.name);
	}

	animation->AddNames({
		_animName,
	});
	animation->InitAnimations(_animations);
}