#include "PlayerAttackComponent.h"
#include"Macro.h"
#include"Mob.h"
#include"Game.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* _owner, const int _damages)
	: Component(_owner)
{
	damages = _damages;
}

void PlayerAttackComponent::SpecialAttack()
{
	Player* _player = Game::GetPlayer();
	const vector<Mob*>& _mobs = RetrieveAllMobsAround<Mob>(_player->GetShapePosition(), 15.0f);
	for (Mob* _mob : _mobs)
	{
		if (!_mob)continue;
		_mob->GetLife()->TakeDamages(GetDamages());
	}
}
