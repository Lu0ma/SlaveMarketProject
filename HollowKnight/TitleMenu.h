#pragma once
#include "Menu.h"
#include "OptionsMenu.h"
#include "AchievementsMenu.h"
#include "QuitGameMenu.h"
#include "SaveSelectorMenu.h"

class TitleMenu : public Menu
{
	vector<Button*> buttons;
	OptionsMenu* options;
	AchievementsMenu* achievement;
	QuitGameMenu* quitGame;
	SaveSelectorMenu* saveSelector;

public:
	virtual void SetStatus(const bool _status)
	{
		options->SetOwner(this);
		Menu::SetStatus(_status);
	}

public:
	TitleMenu(Menu* _owner);

public:
	virtual void Init() override;
};