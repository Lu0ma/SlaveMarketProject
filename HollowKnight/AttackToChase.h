#pragma once
#include "Transition.h"

class AttackToChase : public Transition
{
	virtual bool CanNext() const override;
};

