#pragma once
#include "Menu.h"

class QuitGameMenu : public Menu
{
	vector<Button*> buttons;

public:
	QuitGameMenu(Menu* _owner);

public:
	virtual void Init() override;
};