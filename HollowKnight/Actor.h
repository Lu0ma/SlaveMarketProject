#pragma once
#include "ShapeObject.h"
#include "IManagable.h"
#include "Component.h"
#include "CollisionComponent.h"

using namespace std;

class Actor : public ShapeObject, public IManagable<string>
{
protected:
	vector<Component*> components;
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
	Vector2f GetPosition()const
	{
		return shape->getPosition();
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
	virtual void Init() {};

public:
	virtual void Update(const float _deltaTime);

protected:
	void Destroy(const float _waitingTime = 0.0f);
};