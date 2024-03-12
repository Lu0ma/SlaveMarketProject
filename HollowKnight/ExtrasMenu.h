#pragma once
#include "Menu.h"
#include "Button.h"
class ExtrasMenu : public Menu
{
	Button* backButton;

public:
	ExtrasMenu(Menu* _owner);

public:
	virtual void Init() override;
};