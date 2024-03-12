#include "CollectableActor.h"
#include "Game.h"
#include "Kismet.h"

CollectableActor::CollectableActor(const string& _name, const ShapeData& _data, const float _range,
								   const string& _title, const string& _text, const ItemType& _type) 
								 : Actor(_name, _data)
{
	range = _range;
	data = { _data.path, _title, _text, _type };

	
	//animCollectable = vector<string>();
}

CollectableActor::CollectableActor(const string& _name, const ShapeData& _data, const float _range, const AnimationData& _animData, const ItemType& _type) : Actor(_name, _data)
{
	range = _range;
	data = { _data.path, "", "", _type};

	InitAnimations({
		_animData,
		});
}


void CollectableActor::TryToCollect()
{
	if (!player)
	{
		player = Game::GetPlayer();
	}
	
	const Vector2f& _playerPos = player->GetShapePosition();
	if (Distance(GetShapePosition(), _playerPos) <= range)
	{
		player->GetInventory()->AddItem(1, data);
		SetToRemove(true);
	}
}


void CollectableActor::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	TryToCollect();
}