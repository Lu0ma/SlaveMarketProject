#pragma once
#include "Menu.h"
#include "Timer.h"
#include "PurchaseMenu.h"

class Merchand;

class ShopMenu : public Menu
{
	float timeBeforeOpenShop;
	vector<Button*> buttons;
	vector<SellItem> items;
	Label* descriptionTitle;
	Label* descriptionText;
	Timer* timer;

	Merchand* merchand;
	PurchaseMenu* purchase;

private:
	SellItem GetSellItemByButton(Button* _button)
	{
		const int _buttonsCount = (int)buttons.size();
		for (int _index = 0; _index < _buttonsCount; _index++)
		{
			if (_button == buttons[_index])
			{
				return items[_index];
			}
		}

		return SellItem();
	}

public:
	ShopMenu(Menu* _owner, Merchand* _merchand);

public:
	virtual void Init() override;
	virtual void SetStatus(const bool _status, const bool _applyToWidgets = true) override;
	void Open();
};