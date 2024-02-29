#pragma once
#include "Canvas.h"
#include "Button.h"
#include "Label.h"
#include "ItemWidget.h"

class CharmsMenu
{
	Canvas* canvas;
	Vector2i gridSize;
	Vector2f slotSize;
	Vector2f notchSize;
	Vector2f charmsSelectSize;
	Vector2f cellSize;
	Vector2f gridPos;
	Vector2f windowSize;
	Vector2f halfSize;

	int notches;
	int charms;
	ShapeWidget* pointer;

	vector<Button*> slotsCharms;
	vector<Button*> slotsEquippedCharms;

	Label* descriptionItem;
	Label* titleItem;

public:

	Button* GetFirstAvailableEquippedSlot() const
	{
		for (Button* _button : slotsEquippedCharms)
		{
			if (!_button->GetForeground())
			{
				return _button;
			}
		}

		return nullptr;
	}
	Button* GetFirstAvailableSlotCharms() const
	{
		for (Button* _button : slotsCharms)
		{
			if (!_button->GetForeground())
			{
				return _button;
			}
		}

		return nullptr;
	}

public:
	CharmsMenu();

public:
	void Init();
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}

	void Background();
	void Separator();
	void SelectedCharms();
	void EquippedCharms();
	void Notches();
	void NotchesText();
	void EquippedText();
	void Title();
	void Description();
};
