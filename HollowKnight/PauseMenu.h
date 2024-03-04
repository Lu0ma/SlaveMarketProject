#pragma once
#include "Menu.h"
#include "QuitToMenu.h"

class PauseMenu : public Menu
{
	vector<Button*> buttons;
	QuitToMenu* quitToMenu;

public:
	PauseMenu();

public:
	virtual void Init() override;
};