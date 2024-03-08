#pragma once
#include "Transition.h"

class BossBrain;

class PatrolToChase : public Transition
{
public:
	PatrolToChase(BossBrain* _brain);

public:
	virtual void Init() override;
	virtual bool CanNext() const override;
};