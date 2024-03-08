#pragma once
#include "Transition.h"

class MobBrain;

class PatrolToAttack : public Transition
{
public:
	PatrolToAttack(MobBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};

