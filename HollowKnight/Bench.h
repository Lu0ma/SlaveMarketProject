#pragma once
#include "Actor.h"

class Bench : public Actor
{
public:
	Bench(const ShapeData& _data);

public:
	virtual void Init() override;
};