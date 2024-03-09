#pragma once
#include "Menu.h"
#include "Button.h"
#include <map>

class AudioMenu : public Menu
{
	vector<Button*> buttons;
	map<string, ShapeWidget*> indicators;

	float value;
	float maxValue;
	float minValue;
	float factor;
	Vector2f windowSize;
	Vector2f halfSize;

public:
	AudioMenu(Menu* _owner);

private:
	void MoveIndicator(const string _key, const float _percent);

public:
	virtual void Init() override;
};