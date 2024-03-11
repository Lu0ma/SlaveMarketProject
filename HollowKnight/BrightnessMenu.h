#pragma once
#include "Menu.h"

class BrightnessMenu : public Menu
{
	Button* brightButton;
	ShapeWidget* indicator;
	Button* backButton;

public:
	BrightnessMenu(Menu* _owner);

public:
	virtual void Init() override;
};