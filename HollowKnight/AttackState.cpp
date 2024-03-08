#include "AttackState.h"
#include "Brain.h"

AttackState::AttackState(Brain* _brain) : State(_brain)
{

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