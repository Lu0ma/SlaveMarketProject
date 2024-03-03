#pragma once
#include "Menu.h"
#include "ShapeWidget.h"
#include "Button.h"
#include "OptionsMenu.h"
#include "AchievementsMenu.h"

class TitleMenu : public Menu
{
	vector<Button*> buttons;
	ShapeWidget* pointer;
	OptionsMenu* options;
	AchievementsMenu* achievement;

public:
	TitleMenu(Menu* _owner);

public:
	virtual void Init() override;
};