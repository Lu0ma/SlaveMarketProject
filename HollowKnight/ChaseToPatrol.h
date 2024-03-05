#pragma once
#include "Transition.h"
#include "Brain.h"

class ChaseToPatrol : public Transition
{
public:
	ChaseToPatrol(Brain* _brain);

public:
	virtual void Init() override;

	virtual bool CanNext() const override;

};