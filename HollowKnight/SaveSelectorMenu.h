#pragma once
#include "Menu.h"

class SaveSelectorMenu : public Menu
{
	int saveNumber;
	vector<Button*> buttons;
public:
	SaveSelectorMenu(Menu* _owner);

public:
	void Init();
};

