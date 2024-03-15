#pragma once
#include "Menu.h"
#include "Button.h"
class ExtrasMenu : public Menu
{

public:
	ExtrasMenu(Menu* _owner);

public:
	virtual void Init() override;
};