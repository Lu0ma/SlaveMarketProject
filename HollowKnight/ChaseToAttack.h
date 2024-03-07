#pragma once
#include "Transition.h"

class Brain;

class ChaseToAttack : public Transition
{
public:
	ChaseToAttack(Brain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;

};

