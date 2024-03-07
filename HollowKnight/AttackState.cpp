#include "AttackState.h"
#include "Brain.h"

AttackState::AttackState(Brain* _brain) : State(_brain)
{
	attackToChase = new AttackToChase(_brain);
	transitions.push_back(attackToChase);

	attackToPatrol = new AttackToPatrol(_brain);
	transitions.push_back(attackToPatrol);
}

void AttackState::Init()
{
	attackToChase->Init();
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
