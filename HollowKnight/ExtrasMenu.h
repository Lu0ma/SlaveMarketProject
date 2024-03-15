#pragma once
#include "Menu.h"
#include "CreditsMenu.h"

class ExtrasMenu : public Menu
{
	vector<Button*> buttons;
	CreditsMenu* credits;
	Label* style;
	Button* styleButton;

	int indexStyles;

public:
	ExtrasMenu(Menu* _owner);

public:
	virtual void Init() override;
	void IncreaseIndexStyles();
};