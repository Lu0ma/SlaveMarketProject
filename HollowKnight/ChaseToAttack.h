#pragma once
#include "Transition.h"

class ChaseToAttack : public Transition
{
	virtual bool CanNext() const override;

};

