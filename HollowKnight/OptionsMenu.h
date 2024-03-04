#pragma once
#include "Menu.h"
#include "Button.h"
#include "ControllerMenu.h"
#include "KeyboardMenu.h"

class OptionsMenu : public Menu
{
	vector<Button*> buttons;

	ControllerMenu* controller;
	KeyboardMenu* keyboard;

public:
	OptionsMenu(Menu* _owner);

public:
	virtual void Init() override;
};