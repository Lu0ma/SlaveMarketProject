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
	//attackToDeath->Init(dynamic_cast<MobBrain*>(brain)->GetDeathState());
}

void MobAttackState::Start()
{
	AttackState::Start();

	animation->RunAnimation("Attack", animation->GetCurrentAnimation()->GetDirectionX());

	//Game::GetPlayer()->GetStats()->UpdateLife(-1);

	//new Timer([&]() {
	//	brain->GetBlackBoard()->isInRange = false;
	//}, seconds(0.12f), true, false);
}