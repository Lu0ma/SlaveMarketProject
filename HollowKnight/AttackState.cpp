#include "AttackState.h"
#include "EnemyBrain.h"

AttackState::AttackState(EnemyBrain* _brain) : State(_brain)
{
	attackToPatrol = new AttackToPatrol(_brain);
	transitions.push_back(attackToPatrol);
}

void AttackState::Init()
{
	attackToPatrol->Init();
}

void AttackState::Start()
{
	cout << "Start Attack" << endl;
}

void AttackState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);

}

void AttackState::Stop()
{
	cout << "Stop Attack" << endl;
}
