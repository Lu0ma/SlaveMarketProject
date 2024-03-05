#pragma once
#include "BlackBoard.h"
#include "Component.h"
#include "AttackState.h"
#include "PatrolState.h"
#include "ChaseState.h"

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

public:
	virtual void Update(const float _deltaTime) override;
};

