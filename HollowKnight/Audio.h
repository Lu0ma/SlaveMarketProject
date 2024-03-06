#pragma once
#include "Menu.h"
#include "Button.h"
#include <map>

class Audio : public Menu
{
	vector<Button*> buttons;
	ShapeWidget* pointer;
	map<string, ShapeWidget*> indicators;
	float value;
	float maxValue;
	float minValue;
	float factor;
	Vector2f windowSize;
	Vector2f halfSize;
public:
	Audio(Menu* _owner);
	~Audio();
private:
	void MoveIndicator(const string _key, const float _percent);

public:
	virtual void Init() override;
};

