#pragma once
#include "Menu.h"
#include "BrightnessMenu.h"

class VideoMenu : public Menu
{
	vector<Button*> buttons;

	int resolutionIndex;
	Vector2u resolution;
	Label* resolutionText;

	bool fullScreenActivated;
	Label* fullscreenText;

	int particuleStateIndex;
	Label* particuleText;

	Button* brightnessButton;
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