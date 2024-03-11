#pragma once
#include "Menu.h"
#include "BrightnessMenu.h"
#include "ControllerMenu.h"
#include "KeyboardMenu.h"
#include "Button.h"
#include "AudioMenu.h"

class OptionsMenu : public Menu
{
	vector<Button*> buttons;
	BrightnessMenu* brightness;
	ControllerMenu* controller;
	KeyboardMenu* keyboard;
	ShapeWidget* pointer;
	AudioMenu* audio;

public:
	OptionsMenu(Menu* _owner);

public:
	virtual void Init() override;
};