#pragma once
#include "Transition.h"

class AttackToPatrol : public Transition
{
public:
	AttackToPatrol(Brain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;

};

