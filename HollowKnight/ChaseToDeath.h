#pragma once
#include "Transition.h"

class ChaseToDeath : public Transition
{
public:
	ChaseToDeath(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _nextState) override;
	virtual bool CanNext() const override;
};