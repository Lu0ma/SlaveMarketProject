#pragma once
#include "Menu.h"
#include "Button.h"

class AchievementsMenu : public Menu
{
	Button* backButton;
	ShapeWidget* pointer;

public:
	AchievementsMenu(Menu* _owner);

public:
	virtual void Init() override;
};