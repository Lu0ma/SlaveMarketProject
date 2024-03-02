#include "Boss.h"
#include "Macro.h"
#include "MovementComponent.h"
#include "Game.h"

Boss::Boss(const ShapeData& _data) : Actor("Boss" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;

	MovementComponent* _movement = new MovementComponent(this);
	components.push_back(_movement);
}

void Boss::FacePlayer(Player* _player)
{
	if (animation->GetCurrentAnimation()->GetData().name == "Idle")
	{
		const float _x = GetPosition().x < _player->GetPosition().x ? 1.0f : -1.0f;
		animation->GetCurrentAnimation()->SetDirectionX(_x);
	}
}

void Boss::Update(const float _deltaTime)
{
	Player* _player = Game::GetPlayer();

	FacePlayer(_player);
}
