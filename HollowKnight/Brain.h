#pragma once
#include "Component.h"
#include "BlackBoard.h"
#include "PatrolState.h"
#include "ChaseState.h"
#include "AttackState.h"

#include <vector>

using namespace std;

class Brain : public Component
{
	BlackBoard* blackBoard;

protected:
	State* currentState;
	vector<State*> states;

public:
	BlackBoard* GetBlackBoard()
	{
		return blackBoard;
	}

	template<typename T>
	T* GetState() const
	{
		for (State* _currentState : states)
		{
			if (T* _state = dynamic_cast<T*>(_currentState))
			{
				return _state;
			}
		}
		return nullptr;
	}

public:
	Brain(Actor* _owner);
	~Brain();

public:
	virtual void Init() = 0;
	virtual void Update(const float _deltaTime) override;
};