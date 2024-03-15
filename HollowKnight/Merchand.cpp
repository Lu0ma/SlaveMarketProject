#include "Merchand.h"
#include "Macro.h"

Merchand::Merchand(const ShapeData& _data) : InteractableActor(STRING_ID("Merchand"), _data)
{
	shop = new ShopMenu(nullptr, this);

	const Vector2f& _sizeWait = Vector2f(203.0f, 196.0f);
	const Vector2f& _sizeSell = Vector2f(203.0f, 223.0f);
	const float _speed = 0.2f;

	InitAnimations({
		AnimationData("Wait", Vector2f(0.0f, 84.0f), _sizeWait, READ_RIGHT, true, 5, _speed),
		AnimationData("Sell", Vector2f(0.0f, 294.0f), _sizeSell, READ_RIGHT, true, 5, _speed),

		});
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
	GetComponent<AnimationComponent>()->RunAnimation("Wait", 1);
}