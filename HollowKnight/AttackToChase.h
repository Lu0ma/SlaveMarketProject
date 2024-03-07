#pragma once
#include "Transition.h"

class Brain;

class AttackToChase : public Transition
{
public:
	AttackToChase(Brain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};

