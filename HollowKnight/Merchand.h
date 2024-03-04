#pragma once
#include "InteractableActor.h"
#include "ShopMenu.h"
#include "MerchandAnimationComponent.h"

class Merchand : public InteractableActor
{
	ShopMenu* shop;
	MerchandAnimationComponent* animations;

public:
	void SetShopStatus(const bool _status)
	{
		shop->SetStatus(_status);
	}
	MerchandAnimationComponent* GetAnimations() const
	{
		return animations;
	}

public:
	Merchand(const ShapeData& _data);

public:
	virtual void Init() override;
	virtual void OpenDiscussion() override;
	virtual void CloseDiscussion() override;
};