#pragma once
#include "Menu.h"
#include "Button.h"
#include <map>

class AudioMenu : public Menu
{
	float minValue;
	float maxValue;
	float factor;
	float masterValue;
	float soundValue;
	float musicValue;
	Button* backButton;
	vector<Button*> buttons;
	map<string, ShapeWidget*> indicators;

public:
	AudioMenu(Menu* _owner);

private:
	bool MoveIndicator(const string _key, const float _percent);

public:
	virtual void Init() override;
};