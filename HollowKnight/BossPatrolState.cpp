#include "BossPatrolState.h"
#include "BossBrain.h"

BossPatrolState::BossPatrolState(BossBrain* _brain) : PatrolState(_brain)
{
	patrolToChase = new PatrolToChase(_brain->GetBlackBoard());
	transitions.push_back(patrolToChase);
}


void BossPatrolState::Init()
{
	patrolToChase->Init(dynamic_cast<BossBrain*>(brain)->GetChaseState());
	//patrolToDeath->Init(dynamic_cast<BossBrain*>(brain)->GetDeathState());
}