#pragma once
#include "Transition.h"

class ChaseToPatrol : public Transition
{

public:
	ChaseToPatrol(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};