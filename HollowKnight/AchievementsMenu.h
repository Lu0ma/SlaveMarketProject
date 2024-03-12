#pragma once
#include "Menu.h"
#include "Button.h"
#include "ScrollBar.h"

class AchievementsMenu : public Menu
{
	ScrollBar* handle;
public:
	AchievementsMenu(Menu* _owner);

public:
	virtual void Init() override;
};