#include "ChaseState.h"
#include "Macro.h"
#include "BossBrain.h"

ChaseState::ChaseState(Brain* _brain) : State(_brain)
{
	chaseToPatrol = new ChaseToPatrol(_brain);
	transitions.push_back(chaseToPatrol);
}

void ChaseState::Init()
{
	chaseToPatrol->Init();
}

void ChaseState::Start()
{
	cout << "Start Chase" << endl;
}

void ChaseState::Update(const float _deltaTime)
{
	State::Update(_deltaTime);
	//FacePLayer();
	//cout << "Update Chase" << endl;
}

void ChaseState::Stop()
{	
	cout << "Stop Chase" << endl;
}
