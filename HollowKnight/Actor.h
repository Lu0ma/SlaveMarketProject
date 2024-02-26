#pragma once
#include "ShapeObject.h"
#include "IManagable.h"
#include "Component.h"

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

public:
	Actor(const string& _name, const ShapeData& _data);

private:
	virtual void Register() override;

public:
	virtual void Update(const float _deltaTime);

protected:
	void Destroy(const float _waitingTime = 0.0f);
};