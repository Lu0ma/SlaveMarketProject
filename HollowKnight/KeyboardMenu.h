#pragma once
#include "Menu.h"
#include "Button.h"

class KeyboardMenu : public Menu
{
	Button* backButton;

public:
	KeyboardMenu(Menu* _owner);

public:
	virtual void Init() override;
};