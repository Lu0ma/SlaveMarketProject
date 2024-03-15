#pragma once
#include "Menu.h"

class QuitToMenu : public Menu
{
	vector<Button*> buttons;

public:
	QuitToMenu(Menu* _owner);

public:
	virtual void Init() override;
};