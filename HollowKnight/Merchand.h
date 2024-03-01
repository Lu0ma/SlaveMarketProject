#pragma once
#include "NPC.h"
#include "Canvas.h"
#include "Button.h"
#include "ShapeWidget.h"
#include "Label.h"

class Merchand : public NPC
{
	float timeBeforeOpenShop;
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
	void CloseShop()
	{
		canvas->SetVisibilityStatus(false);
	}

public:
	Merchand(const ShapeData& _data, const vector<string>& _texts = {});

protected:
	virtual void CloseDiscussion() override;

public:
	virtual void Init() override;
	virtual void OpenDiscussion() override;
	//void BuyItem();
};