#pragma once
#include "Transition.h"

class PatrolToChase : public Transition
{

public:
	PatrolToChase(BlackBoard* _blackBoard);

public:
	virtual void Init(State* _state) override;
	virtual bool CanNext() const override;
};