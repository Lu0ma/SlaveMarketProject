#include "AttackState.h"
#include "Brain.h"
#include "MobLifeComponent.h"

AttackState::AttackState(Brain* _brain) : State(_brain)
{
	/*animation = nullptr;
	movement = nullptr;
	inspect = nullptr;*/
	hasAttack = false;

	BlackBoard* _blackBoard = _brain->GetBlackBoard();
	attackToDeath = new AttackToDeath(_blackBoard);
	transitions.push_back(attackToDeath);
}

void AttackState::Start()
{
	//timerInspect->Start();

	cout << brain->GetOwner()->GetID() << "Start Attack" << endl;

	Actor* _owner = brain->GetOwner();

	if (!inspect || !animation || !movement)
	{
		inspect = _owner->GetComponent<InspectComponent>();
		animation = _owner->GetComponent<AnimationComponent>();
		movement = _owner->GetComponent<MobMovementComponent>();
	}



	// Boss -> lance l'anim d'attaque, sur la fin de l'anim si le joueur est toujours en InRange do damage, puis reviens en patrol/chase

	// Mob -> Lance l'anim d'attaque, si le joueur est toujours inRange do damage, puis reviens en patrol

}

void AttackState::Update(const float _deltaTime)
{
	// une fois que l'anim d'atk est faite repasser sur la patrol/chase
	// pas forcement besoin d'un Update ???

	State::Update(_deltaTime);

	if (inspect)
	{
		inspect->HasTarget(brain->GetOwner()->GetShapePosition(), movement->GetLastDirection());
		brain->GetBlackBoard()->isInRange = inspect->IsInRange();
		//brain->GetBlackBoard()->hasTarget = 
	}
	if (brain->GetOwner()->GetComponent<MobLifeComponent>()->GetLife() <= 0)
	{
		brain->GetBlackBoard()->isDead = true;
	}
}

void AttackState::Stop()
{
	//timerInspect->Pause();
	movement->SetDestination(brain->GetOwner()->GetShapePosition());
	cout << brain->GetOwner()->GetID() << "Stop Attack" << endl;
}