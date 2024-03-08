#pragma once
#include "Transition.h"

class BossBrain;

class AttackToChase : public Transition
{
public:
	AttackToChase(BossBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};

