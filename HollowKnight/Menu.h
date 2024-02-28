#pragma once
#include "TitleMenu.h"
#include "Canvas.h"
#include "MusicData.h"

class Menu
{
	Canvas* mainMenu;
	TitleMenu* titleMenu;
	MusicData* music;

public:
	Menu();

private:
	void OpenTitleMenu();

public:
	void Init();
};