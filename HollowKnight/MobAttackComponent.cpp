#include "MobAttackComponent.h"
#include "Actor.h"
#include "Mob.h"
#include "Boss.h"

MobAttackComponent::MobAttackComponent(Actor* _owner, const int _damages) : Component(_owner)
{
	damages = _damages;
	cooldown = 5.0f;
	cooldownTimer = nullptr;
}


void MobAttackComponent::ApplyDamagesToPlayer()
{
	cout << "ApplyDamagesToPlayer" << endl;
	Game::GetPlayer()->GetStats()->UpdateLife(-1);
}


void MobAttackComponent::Attack()
{	
	if (IsAttacking()) return;

	const bool _isRight = Game::GetPlayer()->GetShapePosition().x - owner->GetShapePosition().x >= 0.0f;
	const float _newScaleX = _isRight ? 1.0f : -1.0f;
	//owner->GetDrawable()->setScale(_newScaleX, owner->GetDrawable()->getScale().y);
	owner->GetDrawable()->setScale(-1.0f, owner->GetDrawable()->getScale().y);

	ApplyDamagesToPlayer();
	cooldownTimer = new Timer([&]() { ApplyDamagesToPlayer(); }, seconds(cooldown), true, true);
}

void MobAttackComponent::StopAttack()
{
	cooldownTimer->Stop();
	cooldownTimer = nullptr;
}