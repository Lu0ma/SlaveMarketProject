#pragma once
#include "Menu.h"
#include "ControllerMenu.h"
#include "KeyboardMenu.h"
#include "Button.h"
#include "Audio.h"

class OptionsMenu : public Menu
{
	vector<Button*> buttons;
	ControllerMenu* controller;
	KeyboardMenu* keyboard;
	ShapeWidget* pointer;
	Audio* audio;

public:
	OptionsMenu(Menu* _owner);

public:
	virtual void Init() override;
};