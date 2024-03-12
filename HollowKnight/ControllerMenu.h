#pragma once
#include "Menu.h"

class ControllerMenu : public Menu
{
	Button* backButton;

public:
	ControllerMenu(Menu* _owner);

public:
	virtual void Init() override;
};