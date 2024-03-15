#include "AttackState.h"
#include "Brain.h"

AttackState::AttackState(Brain* _brain) : State(_brain)
{
	attackToDeath = new AttackToDeath(_brain->GetBlackBoard());
	transitions.push_back(attackToDeath);
}


void AttackState::Start()
{
	if (!inspect)
	{
		Actor* _owner = brain->GetOwner();
		animation = _owner->GetComponent<AnimationComponent>();
		inspect = _owner->GetComponent<InspectComponent>();
		attack = _owner->GetComponent<MobAttackComponent>();
	}

	attack->Attack();
}

void AttackState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

	cout << brain->GetOwner()->GetID() << ": Attack" << endl;
	brain->GetBlackBoard()->hasTarget = inspect->HasTarget();
}

void AttackState::Stop()
{
	cout << brain->GetOwner()->GetID() << ": Attack Stop" << endl;
	animation->RunAnimation("Idle", animation->GetCurrentAnimation()->GetDirectionX());
	attack->StopAttack();
}