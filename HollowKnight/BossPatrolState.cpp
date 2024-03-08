#include "BossPatrolState.h"
#include "BossBrain.h"

BossPatrolState::BossPatrolState(BossBrain* _brain) : PatrolState(_brain)
{
	patrolToChase = new PatrolToChase(_brain);
	transitions.push_back(patrolToChase);
}

void BossPatrolState::Init()
{
	PatrolState::Init();
	patrolToChase->Init();
}

void BossPatrolState::Start()
{
	PatrolState::Start();

}

void BossPatrolState::Update(const float _deltaTime)
{
	PatrolState::Update(_deltaTime);

}

void BossPatrolState::Stop()
{
	PatrolState::Stop();

}