#pragma once
#include "Actor.h"

class Enemy : public Actor
{

public:
	Enemy(const string& _name, const ShapeData& _data);
};

