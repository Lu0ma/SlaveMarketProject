#include "PlayerAttackComponent.h"
#include "Game.h"
#include "Lift.h"
#include "Mob.h"
#include "Grub.h"
#include "Macro.h"
#include"Game.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* _owner, const int _damages) : Component(_owner)
{
	canAttack = true;
	damages = _damages;
	range = 50.0f;
	animation = owner->GetComponent<PlayerAnimationComponent>();
}


void PlayerAttackComponent::SpecialAttack()
{
	if (!canAttack) return;

	const Vector2f& _ownerPosition = owner->GetShapePosition();
	const vector<Mob*>& _mobs = RetrieveAllMobsAround<Mob>(_ownerPosition, 45.0f);
	for (Mob* _mob : _mobs)
	{
		if (!_mob) continue;
		
		else
		{
			//_mob->GetLife()->TakeDamages(GetDamages());
			_mob->GetLife()->SetLife(0);
			_mob->Death();
			Game::GetPlayer()->GetStats()->UseMana(10.0f);
		}
	}

	const vector<Mob*>& _mobss = RetrieveAllMobsAround<Mob>(_ownerPosition, -45.0f);
	for (Mob* _mob : _mobss)
	{
		if (!_mob) continue;

		else
		{
			//_mob->GetLife()->TakeDamages(GetDamages());
			_mob->GetLife()->SetLife(0);
			_mob->Death();
			Game::GetPlayer()->GetStats()->UseMana(1.0f);
		}
	}

	const vector<Lift*>& _lifts = Game::GetMap()->GetAllLifts();
	for (Lift* _lift : _lifts)
	{
		_lift->Interact();
	}
	
	const vector<Grub*>& _grubs = RetrieveAllMobsAround<Grub>(_ownerPosition, 45.0f);
	for (Grub* _grub : _grubs)
	{
		
		if (!_grub) continue;

		else
		{
			Game::GetMap()->GetGrub()->GetComponent<AnimationComponent>()->RunAnimation("Escape", -1);
            /*Game::GetMap()->GetGrub()->Destroy(3.0f);*/
		}
	}

	animation->GetCurrentAnimation()->RunAnimation("Special", owner->GetDrawable()->getScale().x);
}

void PlayerAttackComponent::UpAttack()
{
	if (!canAttack) return;

	const Vector2f& _ownerPosition = owner->GetShapePosition();
	const vector<Mob*>& _mobs = RetrieveAllMobAbove<Mob>(_ownerPosition, 50.0f);
	for (Mob* _mob : _mobs)
	{
		if (!_mob) continue;

		else
		{
			//_mob->GetLife()->TakeDamages(GetDamages());
			_mob->GetLife()->SetLife(0);
			_mob->Death();
			Game::GetPlayer()->GetStats()->UseMana(10.0f);
		}
	}


}
