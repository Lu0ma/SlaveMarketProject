#pragma once
#include "Canvas.h"
#include "ShapeWidget.h"
#include "Button.h"

class TitleMenu
{
	Canvas* canvas;
	ShapeWidget* pointer;
	vector<Button*> buttons;

public:
	TitleMenu();

public:
	void Init();
};