#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"
#include "Button.h"

class HUD : public Singleton<HUD>, public IManager<string, Canvas>
{
	vector<Button*> buttons;

public:
	void AddButton(Button* _button)
	{
		buttons.push_back(_button);
	}

public:
	void Interact(const Vector2f& _worldPosition, const Event::EventType& _type);
};