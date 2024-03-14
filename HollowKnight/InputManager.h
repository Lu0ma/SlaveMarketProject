#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "ActionMap.h"

class InputManager : public Singleton<InputManager>, public IManager<string, ActionMap>
{
	Vector2f mousePosition;
	Vector2f worldPosition;


public:
	Vector2f GetMousePosition() const 
	{
		return mousePosition;
	}
	Vector2f GetWorldPosition() const
	{
		return worldPosition;
	}

public:
	bool Update(RenderWindow& _window);

private:
	void UpdateInputs(const Event& _event);
};