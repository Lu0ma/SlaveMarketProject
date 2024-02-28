#pragma once
#include "Canvas.h"

class CharmsMenu
{
	Canvas* canvas;
	Vector2i gridSize;
	Vector2f slotSize;
	Vector2f notchSize;
	Vector2f charmsSelectSize;
	int notches;
	int charms;
public:
	CharmsMenu();

public:
	void Init();
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}
};
