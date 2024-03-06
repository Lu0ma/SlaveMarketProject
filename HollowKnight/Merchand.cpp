#include "Merchand.h"
#include "Game.h"


//Merchand::Merchand(const ShapeData& _data) : InteractableActor(STRING_ID("Merchand"), _data)

#define PATH_ITEM "UIs/Inventory/Core.png"
#define PATH_LANTERN "UIs/Inventory/Lantern.png"

#define PATH_SHOP "UIs/Shop/Shop.png"
#define PATH_POINTER "UIs/Shop/Pointer.png"
#define PATH_GEO "UIs/Shop/Geo.png"
#define FONT "Font.ttf"

Merchand::Merchand(const ShapeData& _data)
				  : InteractableActor(STRING_ID("Merchand"), _data)

{
	shop = new ShopMenu(nullptr, this);

	animation = new MerchandAnimationComponent(this);
	components.push_back(animation);
	animation->GetCurrentAnimation()->RunAnimation("Wait", 1);

}


void Merchand::Init()
{
	InteractableActor::Init();

	shop->SetStatus(false);
}

void Merchand::OpenDiscussion()
{
	InteractableActor::OpenDiscussion();
	shop->SetStatus(true);
}

void Merchand::CloseDiscussion()
{
	InteractableActor::CloseDiscussion();

	shop->SetStatus(false);

	GetAnimation()->GetCurrentAnimation()->RunAnimation("Wait", 1);
}

//void Merchand::BuyItem()
//{
//
//}

