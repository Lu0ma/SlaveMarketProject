#pragma once
#include "Transition.h"

class BossBrain;

class ChaseToAttack : public Transition
{
public:
	ChaseToAttack(BossBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;

};

