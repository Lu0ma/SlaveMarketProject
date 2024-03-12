#pragma once
#include "Menu.h"
#include "CharmWidget.h"

class CharmsMenu : public Menu
{
	Vector2i gridSize;
	Vector2f slotSize;
	Vector2f notchSize;
	Vector2f charmsSelectSize;
	Vector2f cellSize;
	Vector2f gridPos;
	Vector2f windowSize;
	Vector2f halfSize;

	int notches;
	int charmsCount;

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

private:
	void Background();
	void Separator();
	void SelectedCharms();
	void SlotCharms();
	void Notches();
	void NotchesText();
	void EquippedText();
	void Title();
	void Description();

public:
	void Init();
};