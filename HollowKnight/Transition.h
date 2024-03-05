#pragma once

class State;
class Brain;
struct BlackBoard;

class Transition
{
protected:
	State* nextState;
	BlackBoard* blackBoard;
	Brain* brain;

public:
	State* GetNextState() const 
	{
		return nextState;
	}

public:
	Transition(Brain* _brain);

public:
	virtual void Init() = 0;
	virtual bool CanNext() const = 0;
};