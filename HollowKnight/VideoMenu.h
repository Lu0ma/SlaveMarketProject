#pragma once
#include "Menu.h"
#include "BrightnessMenu.h"

class VideoMenu : public Menu
{
	vector<Button*> buttons;
	BrightnessMenu* brightness;

public:
	VideoMenu(Menu* _owner);

private:
	void ChangeResolution();
	void ToggleFullScreen();
	void ChangeParticule();

public:
	virtual void Init() override;
};