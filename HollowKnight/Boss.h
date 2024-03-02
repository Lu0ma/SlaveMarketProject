#pragma once
#include "Actor.h"
#include "AnimationComponent.h"
#include "Game.h"

class Boss : public Actor
{
	Vector2f startPosition;

protected:
	AnimationComponent* animation;
	
public:
	Boss(const ShapeData& _data);

public:
	void FacePlayer(Player* _player);
	virtual void Update(const float _deltaTime) override;
};