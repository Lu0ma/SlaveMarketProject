#pragma once
#include "Transition.h"
#include "Brain.h"

class PatrolToChase : public Transition
{
public:
	PatrolToChase(Brain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};