#pragma once
#include "Menu.h"
#include "Button.h"

class AchievementsMenu : public Menu
{
public:
	AchievementsMenu(Menu* _owner);

public:
	virtual void Init() override;
};