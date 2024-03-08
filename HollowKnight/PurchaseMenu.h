#pragma once
#include "Menu.h"
#include "Button.h"

struct SellItem
{
	string path;
	int price;
	string title;
	string text;
};

class PurchaseMenu : public Menu
{
	bool canBuy;
	vector<Button*> buttons;
	SellItem item;
	Label* title;
	ShapeWidget* icon;
	Label* price;
	Label* buyLabel;
	Label* warnMessage;

public:
	PurchaseMenu(Menu* _owner);

public:
	virtual void Init() override;
	void SetItem(const SellItem& _item);
};