#pragma once
#include "NPC.h"
#include "Canvas.h"
#include "Button.h"
#include "ShapeWidget.h"
#include "Label.h"

class Merchand : public NPC
{
	Canvas* canvas;
	vector<Button*> buttons;
	ShapeWidget* pointer = nullptr;
	Label* descriptionTitle = nullptr;
	Label* descriptionText = nullptr;

public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

public:
	Merchand();

public:
	void Init();
	//void BuyItem();
};