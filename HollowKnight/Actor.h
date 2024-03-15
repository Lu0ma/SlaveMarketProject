#pragma once
#include "ShapeObject.h"
#include "IManagable.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"

using namespace std;

class Actor : public ShapeObject, public IManagable<string>
{

protected:
	vector<Component*> components;
	CollisionComponent* collision;
	AnimationComponent* animation;
public:
	template <typename T>
	T* GetComponent() const
	{
		for (Component* _currentComponent : components)
		{
			if (T* _component = dynamic_cast<T*>(_currentComponent))
			{
				return _component;
			}
		}

		return nullptr;
	}
	FloatRect GetBounds() const
	{
		return shape->getGlobalBounds();
	}
public:
	Actor(const string& _name, const ShapeData& _data, const CollisionType& _collisionType = CT_NONE);
	~Actor();

protected:
	virtual void Register() override;
	
private:

public:
	virtual void Init();
	virtual void Update(const float _deltaTime);
	void Destroy(const float _waitingTime = 0.0f);
	void InitAnimations(const vector<AnimationData>& _animations);
};