#pragma once
#include "Transition.h"
#include <vector>
#include "Timer.h"

#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "InspectComponent.h"

using namespace std;

class Brain;

class State
{
	Transition* nextTransition;

protected:
	Brain* brain;
	vector<Transition*> transitions;

public:
	Transition* GetNextTransition()
	{
		Transition* _nextTransition = nextTransition;
		nextTransition = nullptr;

		return _nextTransition; 
	}

public:
	State(Brain* _brain);
	~State();

public:
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Update(const float _deltaTime);
	virtual void Stop() = 0;
};