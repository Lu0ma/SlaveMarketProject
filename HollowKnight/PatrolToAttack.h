#pragma once
#include "Transition.h"

class PatrolToAttack : public Transition
{

public:
	PatrolToAttack(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};