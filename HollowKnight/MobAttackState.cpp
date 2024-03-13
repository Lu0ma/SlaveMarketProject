#include "MobAttackState.h"
#include "MobBrain.h"
#include "Game.h"

MobAttackState::MobAttackState(Brain* _brain) : AttackState(_brain)
{
	attackToPatrol = new AttackToPatrol(_brain->GetBlackBoard());
	transitions.push_back(attackToPatrol);
}


void MobAttackState::Init()
{
	attackToPatrol->Init(dynamic_cast<MobBrain*>(brain)->GetPatrolState());
}

void MobAttackState::Start()
{
	cout << "MobAttack START" << endl;
	AttackState::Start();

	animation->RunAnimation("Bounce", animation->GetCurrentAnimation()->GetDirectionX());

	Game::GetPlayer()->GetStats()->UpdateLife(-1);

	new Timer([&]() {
		brain->GetBlackBoard()->hasTarget = false;
		}, seconds(0.5f), true, false);
}
