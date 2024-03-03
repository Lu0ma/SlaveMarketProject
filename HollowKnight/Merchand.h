#pragma once
#include "NPC.h"
#include "Canvas.h"
#include "Button.h"
#include "ShapeWidget.h"
#include "Label.h"
#include "Timer.h"
#include"MerchandAnimationComponent.h"

class Merchand : public NPC
{
	float timeBeforeOpenShop;
	Canvas* canvas;
	vector<Button*> buttons;
	ShapeWidget* pointer;
	Label* descriptionTitle;
	Label* descriptionText;
	Timer* timer;
	MerchandAnimationComponent* animations;

public:
	MerchandAnimationComponent* GetAnimations()const
	{
		return animations;
	}

public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}
	void CloseShop()
	{
		canvas->SetVisibilityStatus(false);
		timer = nullptr;
	}

public:
	Merchand(const ShapeData& _data, const vector<string>& _texts = {});

public:
	virtual void Init() override;
	virtual void OpenDiscussion() override;
	virtual void CloseDiscussion() override;
	//void BuyItem();
};