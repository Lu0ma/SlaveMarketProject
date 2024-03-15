#pragma once
#include "InteractableActor.h"
#include "ShopMenu.h"
#include"HUD.h"

class Merchand : public InteractableActor
{
	ShopMenu* shop;

public:
	void SetShopStatus(const bool _status)
	{
		shop->SetStatus(_status);
	}

public:
	Merchand(const ShapeData& _data);

public:
	virtual void Init() override;
	virtual void OpenDiscussion() override;
	virtual void CloseDiscussion() override;
};