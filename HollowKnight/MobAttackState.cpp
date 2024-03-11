#include "MobAttackState.h"
#include "MobBrain.h"

MobAttackState::MobAttackState(Brain* _brain) : AttackState(_brain)
{
	attackToPatrol = new AttackToPatrol(_brain->GetBlackBoard());
	transitions.push_back(attackToPatrol);
}


void MobAttackState::Init()
{
	attackToPatrol->Init(dynamic_cast<MobBrain*>(brain)->GetPatrolState());
}