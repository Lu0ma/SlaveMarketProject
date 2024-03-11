#include "AttackState.h"
#include "Brain.h"

AttackState::AttackState(Brain* _brain) : State(_brain)
{
	animation = nullptr;
	movement = nullptr;
	inspect = nullptr;
}


void AttackState::Start()
{
	Actor* _owner = brain->GetOwner();

	if (!inspect || !animation || !movement)
	{
		inspect = _owner->GetComponent<InspectComponent>();
		animation = _owner->GetComponent<AnimationComponent>();
		movement = _owner->GetComponent<MobMovementComponent>();
	}

	// Boss -> lance l'anim d'attaque, sur la fin de l'anim si le joueur est toujours en InRange do damage, puis reviens en patrol/chase

	// Mob -> Lance l'anim d'attaque, si le joueur est toujours inRange do damage, puis reviens en patrol

	cout << "Start Attack" << endl;
}

void AttackState::Update(const float _deltaTime)
{
	// une fois que l'anim d'atk est faite repasser sur la patrol/chase
	// pas forcement besoin d'un Update ???

	State::Update(_deltaTime);

	if (inspect)
	{
		brain->GetBlackBoard()->hasTarget = inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetDestination());
		brain->GetBlackBoard()->isInRange = inspect->IsInRange();
	}
}

void AttackState::Stop()
{
	cout << "Stop Attack" << endl;
}