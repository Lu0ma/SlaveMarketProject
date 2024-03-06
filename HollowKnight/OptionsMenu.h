#pragma once
#include "Menu.h"
#include "Button.h"
#include "Audio.h"

class OptionsMenu : public Menu
{
	vector<Button*> buttons;
	ShapeWidget* pointer;
	Audio* audio;

public:
	OptionsMenu(Menu* _owner);

public:
	virtual void Init() override;
};