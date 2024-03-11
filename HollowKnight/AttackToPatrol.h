#pragma once
#include "Transition.h"

class AttackToPatrol : public Transition
{

public:
	AttackToPatrol(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};