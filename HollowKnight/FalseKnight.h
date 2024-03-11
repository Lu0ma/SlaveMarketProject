#pragma once
#include "Boss.h"

class FalseKnight : public Boss
{

public:
	FalseKnight(const ShapeData& _data);

public:
	virtual void Init() override;
};