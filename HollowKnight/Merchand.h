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
	ShapeWidget* pointer;
	Label* descriptionTitle;
	Label* descriptionText;

public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

public:
	Merchand(const Vector2f& _position, const Vector2f& _size);

public:
	void Init();
	//void BuyItem();

	void Update();
};