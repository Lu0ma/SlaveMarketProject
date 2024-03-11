#pragma once
#include "Transition.h"

class AttackToChase : public Transition
{

public:
	AttackToChase(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};