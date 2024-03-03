#pragma once
#include "Menu.h"
#include "TitleMenu.h"

class MainMenu : public Menu
{
	TitleMenu* titleMenu;

public:
	MainMenu();

private:
	void OpenTitleMenu();

public:
	virtual void Init() override;
};