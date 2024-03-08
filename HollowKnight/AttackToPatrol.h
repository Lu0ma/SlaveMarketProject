#pragma once
#include "Transition.h"

class EnemyBrain;

class AttackToPatrol : public Transition
{
public:
	AttackToPatrol(EnemyBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};

