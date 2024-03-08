#pragma once
#include "Brain.h"

class EnemyBrain : public Brain
{

public:
	EnemyBrain(Actor* _owner);
	~EnemyBrain();
};

