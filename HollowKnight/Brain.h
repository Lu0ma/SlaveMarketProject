#pragma once
#include "Component.h"
#include "BlackBoard.h"

#include "PatrolState.h"
#include "ChaseState.h"
#include "AttackState.h"

class Brain : public Component
{
	BlackBoard blackBoard;

protected:
	State* currentState;

	AttackState* attack;
	PatrolState* patrol;
	ChaseState* chase;

public:
	BlackBoard& GetBlackBoard()
	{
		return blackBoard;
	}
	AttackState* GetAttackState() const
	{
		return attack;
	}
	PatrolState* GetPatrolState() const
	{
		return patrol;
	}
	ChaseState* GetChaseState() const
	{
		return chase;
	}

public:
	Brain(Actor* _owner);
	~Brain();

public:
	virtual void Update(const float _deltaTime) override;
};