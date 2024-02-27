#pragma once
#include "TitleMenu.h"
#include "Canvas.h"

class Menu
{
	Canvas* mainMenu;
	TitleMenu* titleMenu;

public:
	Menu();

private:
	void OpenTitleMenu();

public:
	void Init();
};