#pragma once
#include "Menu.h"
#include "OptionsMenu.h"
#include "AchievementsMenu.h"
#include "QuitGameMenu.h"

class TitleMenu : public Menu
{
	vector<Button*> buttons;
	OptionsMenu* options;
	AchievementsMenu* achievement;
	QuitGameMenu* quitGame;

public:
	TitleMenu(Menu* _owner);

public:
	virtual void Init() override;
};