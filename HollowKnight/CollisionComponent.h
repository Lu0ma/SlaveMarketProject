#pragma once
#include "Component.h"
#include <iostream>
using namespace std;
class CollisionComponent : public Component
{

public:
	bool CheckCollision(Actor* _currentActor);
};

