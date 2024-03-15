#include "TriggerBox.h"
#include "Game.h"

TriggerBox::TriggerBox(const ShapeData& _data, const function<void()>& _callback)
					 : Actor(STRING_ID("TriggerBox"), _data, CT_OVERLAP)
{
	callback = _callback;
	boxRect = FloatRect();
	shape->setFillColor(Color::Blue);
}


void TriggerBox::TryToTrigger()
{
	const FloatRect& _boxRect = collision->GetBoxCollision()->GetDrawable()->getGlobalBounds();
	const FloatRect& _playerRect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();

	if (_boxRect.intersects(_playerRect))
	{
		callback();
	}
}


void TriggerBox::Init()
{
	boxRect = collision->GetBoxCollision()->GetDrawable()->getGlobalBounds();
}

void TriggerBox::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	TryToTrigger();
}