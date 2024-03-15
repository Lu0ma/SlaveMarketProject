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

	bool canUpdateFrameRate;
	bool capFrameRate;
	int frameRate;
	int maxFrameRate;
	int frameRateFactor;
	Button* frameRateButton;
	Label* frameRateText;
	Button* checkBox;

	Button* brightnessButton;
	BrightnessMenu* brightness;

public:
	VideoMenu(Menu* _owner);

private:
	void ChangeResolution();
	void ToggleFullScreen();
	void ChangeParticule();
	void UpdateFrameRate(const int _factor);
	void ToggleCapFrameRate();

public:
	virtual void Init() override;
};