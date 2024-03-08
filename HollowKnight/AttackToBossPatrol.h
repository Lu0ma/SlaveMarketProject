#pragma once
#include "Transition.h"

class BossBrain;

class AttackToBossPatrol : public Transition
{
public:
	AttackToBossPatrol(BossBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};

