#include "BossAttackState.h"
#include "BossBrain.h"

BossAttackState::BossAttackState(Brain* _brain) : AttackState(_brain)
{
	attackToChase = new AttackToChase(_brain->GetBlackBoard());
	transitions.push_back(attackToChase);
}

void BossAttackState::Init()
{
	attackToChase->Init(dynamic_cast<BossBrain*>(brain)->GetChaseState());
}