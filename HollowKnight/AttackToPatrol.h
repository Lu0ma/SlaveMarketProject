#pragma once
#include "Transition.h"

class AttackToPatrol : public Transition
{
	virtual bool CanNext() const override;

};

