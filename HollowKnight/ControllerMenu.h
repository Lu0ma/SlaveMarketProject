#pragma once
#include "Menu.h"
#include "Button.h"

class ControllerMenu : public Menu
{

public:
	ControllerMenu(Menu* _owner);

public:
	virtual void Init() override;
};