#include "MobPatrolState.h"
#include "MobBrain.h"

MobPatrolState::MobPatrolState(Brain* _brain) : PatrolState(_brain)
{
	patrolToAttack = new PatrolToAttack(_brain->GetBlackBoard());
	transitions.push_back(patrolToAttack);
}


void MobPatrolState::Init()
{
	patrolToAttack->Init(dynamic_cast<MobBrain*>(brain)->GetAttackState());
	//patrolToDeath->Init(dynamic_cast<MobBrain*>(brain)->GetDeathState());
}