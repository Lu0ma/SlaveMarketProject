#pragma once
#include "State.h"

class DeathState : public State
{
public:
	DeathState(Brain* _brain);

public:
	virtual void Start() override;
	virtual void Update(const float _deltaTime) override;
	virtual void Stop() override;
	virtual void Init() override;
};

