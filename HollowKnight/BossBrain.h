#pragma once
#include "EnemyBrain.h"
#include "ChaseState.h"

class BossBrain : public EnemyBrain
{
public:
	BossBrain(Actor* _owner);
	~BossBrain();
};