#pragma once
#include "Menu.h"
#include "Button.h"

class OptionsMenu : public Menu
{
	vector<Button*> buttons;
	ShapeWidget* pointer;

public:
	OptionsMenu(Menu* _owner);

public:
	virtual void Init() override;
};