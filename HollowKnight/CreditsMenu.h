#pragma once
#include "Menu.h"

class CreditsMenu : public Menu
{	
public:
	CreditsMenu(Menu* _owner);

public:
	virtual void Init() override;
};