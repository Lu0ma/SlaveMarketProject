#include "BossAttackState.h"
#include "BossBrain.h"

BossAttackState::BossAttackState(BossBrain* _brain) : AttackState(_brain)
{
	attackToChase = new AttackToChase(_brain);
	transitions.push_back(attackToChase);
}

void BossAttackState::Init()
{
	AttackState::Init();
	attackToChase->Init();
}

void BossAttackState::Start()
{
}

void BossAttackState::Update(const float _deltaTime)
{
}

void BossAttackState::Stop()
{
}
