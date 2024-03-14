#pragma once
#include "Menu.h"

class BrightnessMenu : public Menu
{
	float minValue;
	float maxValue;
	float factor;
	Button* brightButton;
	ShapeWidget* indicator;

public:
	BrightnessMenu(Menu* _owner);

public:
	virtual void Init() override;
	bool MoveIndicator(const float _percent);
};