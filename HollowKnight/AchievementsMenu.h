#pragma once
#include "Menu.h"
#include "Button.h"

class AchievementsMenu : public Menu
{
	Button* backButton;

public:
	AchievementsMenu(Menu* _owner);

public:
	virtual void Init() override;
};