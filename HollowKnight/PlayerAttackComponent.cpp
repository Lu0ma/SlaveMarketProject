#include "PlayerAttackComponent.h"
#include "Game.h"
#include "Lift.h"
#include "Mob.h"
#include "Macro.h"
#include"Game.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* _owner, const int _damages) : Component(_owner)
{
	damages = _damages;
	range = 50.0f;
	animation = owner->GetComponent<PlayerAnimationComponent>();
}


void PlayerAttackComponent::SpecialAttack()
{
	const Vector2f& _ownerPosition = owner->GetShapePosition();
	const vector<Mob*>& _mobs = RetrieveAllMobsAround<Mob>(_ownerPosition, 15.0f);
	for (Mob* _mob : _mobs)
	{
		if (!_mob) continue;
		
		else
		{
			_mob->GetLife()->TakeDamages(GetDamages());
			Game::GetPlayer()->GetStats()->UseMana(1.0f);
		}
	}

	const vector<Lift*>& _lifts = Game::GetMap()->GetAllLifts();
	for (Lift* _lift : _lifts)
	{
		_lift->Interact();
	}

	animation->GetCurrentAnimation()->RunAnimation("Special", owner->GetDrawable()->getScale().x);
}