#include "CollectableActor.h"
#include "Game.h"
#include "Kismet.h"

CollectableActor::CollectableActor(const string& _name, const ShapeData& _data, const float _range,
								   const string& _title, const string& _text, const ItemType& _type) 
								 : Actor(_name, _data)
{
	range = _range;
	data = { _data.path, _title, _text, _type };

	animation = nullptr;
	animCollectable = vector<string>();
}

CollectableActor::CollectableActor(const string& _name, const ShapeData& _data, const float _range, const ItemType& _type) : Actor(_name, _data)
{
	range = _range;
	data = { _data.path, "", "", _type};

	animation = new AnimationComponent(this);
	animCollectable = vector<string>();

	animCollectable.push_back("Spawn");
	animCollectable.push_back("Take");

	const Vector2f& _size = Vector2f(182.0f, 178.0f);
	const float _speed = 0.1f;

	animation->InitAnimations({
		AnimationData("Spawn", Vector2f(0.0f, 23.0f), _size, READ_RIGHT, false, 1, _speed),
		AnimationData("Take", Vector2f(0.0f, 23.0f), _size, READ_RIGHT, false, 4, _speed), 
		
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