#pragma once
#include "Brain.h"
#include "BossPatrolState.h"
#include "BossAttackState.h"

class EnemyBrain : public Brain
{

public:
	EnemyBrain(Actor* _owner);
};