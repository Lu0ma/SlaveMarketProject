#include "Boss.h"
#include "Macro.h"

Boss::Boss(const ShapeData& _data) : Actor("Boss" + to_string(GetUniqueID()), _data)
{
	startPosition = _data.position;

	MovementComponent* _movement = new MovementComponent(this);
	components.push_back(_movement);

	movement = new MovementComponent(this);
	movement->SetSpeed(0.1f);
	components.push_back(movement);

	attack = new MobAttackComponent(this, 1);
	components.push_back(attack);

	life = new MobLifeComponent(this, 3);
	components.push_back(life);
}

void Boss::FacePlayer(Player* _player)
{
		const float _x = GetPosition().x < _player->GetPosition().x ? 1.0f : -1.0f;
		animation->GetCurrentAnimation()->SetDirectionX(_x);
}

void Boss::Update(const float _deltaTime)
{
	Player* _player = Game::GetPlayer();

	if (animation->GetCurrentAnimation()->GetData().name == "Idle")
	{
		FacePlayer(_player);
		Attack(_player);
	}
}