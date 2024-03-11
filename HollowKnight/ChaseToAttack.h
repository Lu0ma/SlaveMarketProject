#pragma once
#include "Transition.h"


class ChaseToAttack : public Transition
{

public:
	ChaseToAttack(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};