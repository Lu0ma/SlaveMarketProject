#pragma once
#include "Actor.h"
#include "Player.h"

class CollectableActor : public Actor
{
	float range;
	ItemData data;
	Player* player;

public:
	CollectableActor(const string& _name, const ShapeData& _data, const float _range,
					 const string& _title, const string& _text, const ItemType& _type);

private:
	void TryToCollect();
	
public:
	virtual void Update(const float _deltaTime) override;
};