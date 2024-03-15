#pragma once
#include "Transition.h"

class AttackToDeath : public Transition
{
public:
	AttackToDeath(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};