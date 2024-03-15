#pragma once
#include "Transition.h"

class PatrolToDeath : public Transition
{
public:
	PatrolToDeath(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};